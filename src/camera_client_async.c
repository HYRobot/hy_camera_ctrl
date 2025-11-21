#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <cjson/cJSON.h>

// 包含 Redis ae 事件库
#include "ae.h"

#include "camera_client_async.h"

#define BUF_SIZE 1024
#define TIMEOUT_MS 2000 // 2秒超时

// ==========================================
// 内部结构体定义 (对外部隐藏)
// ==========================================

// 链表节点：代表一个正在等待响应的请求
typedef struct RequestNode {
    struct CameraClient *client; // 指向父对象的指针
    char cmd_id_str[32];         // 唯一标识符 (如 "cmd_10")
    long long timer_id;          // ae库分配的定时器ID
    cmd_callback_t cb;           // 用户回调函数
    void *privdata;              // 用户私有数据
    struct RequestNode *next;    // 双向链表 next
    struct RequestNode *prev;    // 双向链表 prev
} RequestNode;

// 客户端主结构体
struct CameraClient {
    int fd;                         // UDP Socket 文件描述符
    aeEventLoop *el;                // 事件循环指针
    struct sockaddr_in server_addr; // 目标地址
    RequestNode *pending_head;      // 待处理请求链表的头指针
};

// ==========================================
// 内部辅助函数 (Forward Declaration)
// ==========================================

static void remove_request_node(CameraClient *client, RequestNode *node);
static RequestNode* find_request_by_id(CameraClient *client, const char *cmd_id);
static int set_nonblock(int fd);

// ==========================================
// 事件回调处理
// ==========================================

/**
 * [事件] 请求超时回调
 * 当服务器在 TIMEOUT_MS 时间内没有回复时触发
 */
static int on_request_timeout(struct aeEventLoop *eventLoop, long long id, void *clientData) {
    RequestNode *node = (RequestNode *)clientData;
    CameraClient *client = node->client;

    // printf("[Async] Timeout triggered for %s\n", node->cmd_id_str);

    // 1. 触发用户回调 (传递超时错误码)
    if (node->cb) {
        node->cb(CAM_ERR_TIMEOUT, node->privdata);
    }

    // 2. 从链表中移除该节点
    remove_request_node(client, node);

    // 3. 释放节点内存
    // 注意：这里不需要调用 aeDeleteTimeEvent，因为返回 AE_NOMORE 会自动删除当前定时器
    free(node);

    return AE_NOMORE;
}

/**
 * [事件] Socket 可读回调
 * 当 UDP 端口收到数据时触发
 */
static void on_socket_readable(struct aeEventLoop *eventLoop, int fd, void *clientData, int mask) {
    CameraClient *client = (CameraClient *)clientData;
    char buffer[BUF_SIZE];
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);

    // 1. 读取数据
    ssize_t n = recvfrom(fd, buffer, BUF_SIZE - 1, 0, (struct sockaddr *)&addr, &len);
    if (n <= 0) return;

    buffer[n] = '\0'; // 确保是合法字符串

    // 2. 解析 JSON
    cJSON *json = cJSON_Parse(buffer);
    if (!json) {
        // JSON 格式错误，忽略
        return;
    }

    // 3. 提取 cmd_id
    cJSON *cmd_item = cJSON_GetObjectItemCaseSensitive(json, "cmd_id");
    if (!cJSON_IsString(cmd_item) || (cmd_item->valuestring == NULL)) {
        cJSON_Delete(json);
        return;
    }

    // 4. 在链表中查找对应的请求
    RequestNode *node = find_request_by_id(client, cmd_item->valuestring);
    
    if (node) {
        // 找到请求了！
        
        // A. 取消超时定时器 (因为已经收到回复了)
        aeDeleteTimeEvent(eventLoop, node->timer_id);

        // B. 获取 ret 结果码
        int ret_code = CAM_ERR_NO_RET;
        cJSON *ret_item = cJSON_GetObjectItemCaseSensitive(json, "ret");
        if (cJSON_IsNumber(ret_item)) {
            ret_code = ret_item->valueint;
        }

        // C. 执行用户回调
        if (node->cb) {
            node->cb(ret_code, node->privdata);
        }

        // D. 清理节点
        remove_request_node(client, node);
        free(node);
    } else {
        // 没找到请求，可能是超时的响应，或者是未知的广播，忽略
        // printf("[Async] Ignored response for unknown cmd: %s\n", cmd_item->valuestring);
    }

    cJSON_Delete(json);
}

// ==========================================
// 公共 API 实现
// ==========================================

CameraClient* camera_client_init(aeEventLoop *el, const char *server_ip, int port) {
    if (!el || !server_ip) return NULL;

    CameraClient *client = (CameraClient *)calloc(1, sizeof(CameraClient));
    if (!client) return NULL;

    client->el = el;
    client->pending_head = NULL;

    // 1. 创建 UDP Socket
    client->fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (client->fd < 0) {
        free(client);
        return NULL;
    }

    // 2. 设置非阻塞 (关键)
    if (set_nonblock(client->fd) < 0) {
        close(client->fd);
        free(client);
        return NULL;
    }

    // 3. 配置目标地址
    memset(&client->server_addr, 0, sizeof(client->server_addr));
    client->server_addr.sin_family = AF_INET;
    client->server_addr.sin_port = htons(port);
    client->server_addr.sin_addr.s_addr = inet_addr(server_ip);

    // 4. 注册读事件 (永久监听)
    // 当 Socket 有数据来时，ae 库会调用 on_socket_readable
    if (aeCreateFileEvent(el, client->fd, AE_READABLE, on_socket_readable, client) == AE_ERR) {
        close(client->fd);
        free(client);
        return NULL;
    }

    return client;
}

int camera_client_send(CameraClient *client, const char *method, cmd_callback_t cb, void *privdata) {
    if (!client || !method) return -1;

    static int global_cmd_seq = 0; // 静态计数器

    // 1. 创建请求节点
    RequestNode *node = (RequestNode *)calloc(1, sizeof(RequestNode));
    if (!node) return CAM_ERR_MALLOC;

    node->client = client;
    node->cb = cb;
    node->privdata = privdata;
    
    // 生成唯一的 cmd_id
    snprintf(node->cmd_id_str, sizeof(node->cmd_id_str), "cmd_%d", global_cmd_seq++);

    // 2. 构建 JSON 数据
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "method", method);
    cJSON_AddStringToObject(root, "cmd_id", node->cmd_id_str);

    char *json_str = cJSON_PrintUnformatted(root);
    if (!json_str) {
        cJSON_Delete(root);
        free(node);
        return CAM_ERR_MALLOC;
    }

    // 3. 发送 UDP 数据
    // 由于是 UDP 且是非阻塞，通常直接发送即可。
    // 严谨场景下可检查 sendto 返回值处理 EAGAIN，但 UDP 缓冲区一般足够大。
    ssize_t sent = sendto(client->fd, json_str, strlen(json_str), 0, 
                          (struct sockaddr *)&client->server_addr, sizeof(client->server_addr));

    free(json_str);
    cJSON_Delete(root);

    if (sent < 0) {
        free(node);
        return -1; // 发送失败
    }

    // 4. 将节点加入链表 (头部插入)
    node->next = client->pending_head;
    if (client->pending_head) {
        client->pending_head->prev = node;
    }
    client->pending_head = node;

    // 5. 创建超时定时器
    // 如果 TIMEOUT_MS 后还没被 on_socket_readable 清除，则触发 on_request_timeout
    long long timer_id = aeCreateTimeEvent(client->el, TIMEOUT_MS, on_request_timeout, node, NULL);
    node->timer_id = timer_id;

    return 0; // 成功入队
}

void camera_client_destroy(CameraClient *client) {
    if (!client) return;

    // 1. 移除 Socket 监听
    aeDeleteFileEvent(client->el, client->fd, AE_READABLE);
    close(client->fd);

    // 2. 清理所有待处理的请求
    RequestNode *curr = client->pending_head;
    while (curr) {
        RequestNode *next = curr->next;
        
        // 删除对应的定时器
        aeDeleteTimeEvent(client->el, curr->timer_id);
        
        // 可选：在此处触发回调通知用户“客户端被销毁”
        // if (curr->cb) curr->cb(-999, curr->privdata);

        free(curr);
        curr = next;
    }

    free(client);
}

// ==========================================
// 内部辅助函数实现
// ==========================================

// 辅助：将 socket 设为非阻塞
static int set_nonblock(int fd) {
    int flags;
    if ((flags = fcntl(fd, F_GETFL)) == -1) return -1;
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) return -1;
    return 0;
}

// 辅助：双向链表移除节点
static void remove_request_node(CameraClient *client, RequestNode *node) {
    if (node->prev) {
        node->prev->next = node->next;
    } else {
        // 如果是头节点
        client->pending_head = node->next;
    }

    if (node->next) {
        node->next->prev = node->prev;
    }
}

// 辅助：根据 ID 查找节点
static RequestNode* find_request_by_id(CameraClient *client, const char *cmd_id) {
    RequestNode *curr = client->pending_head;
    while (curr) {
        if (strcmp(curr->cmd_id_str, cmd_id) == 0) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}