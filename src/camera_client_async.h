#ifndef CAMERA_CLIENT_ASYNC_H
#define CAMERA_CLIENT_ASYNC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ae.h" // 需要引用 Redis ae 库的头文件

// --- 错误码定义 ---
// 大于等于0 的值为服务器返回的业务 ret
// 小于0 的值为本地通信错误
#define CAM_RET_SUCCESS       0
#define CAM_ERR_TIMEOUT      -4  // 等待响应超时
#define CAM_ERR_NO_RET       -5  // 响应中没有 'ret' 字段
#define CAM_ERR_MALLOC       -6  // 内存分配失败

// --- 类型定义 ---

/**
 * 相机客户端句柄 (不透明结构体)
 * 具体定义在 .c 文件中，隐藏内部实现细节
 */
typedef struct CameraClient CameraClient;

/**
 * 回调函数类型定义
 * @param ret_code: 
 * >= 0: 服务器返回的成功/失败码 (例如 0 表示成功)
 * < 0 : 发生了网络错误或超时 (参见上面的 CAM_ERR_*)
 * @param privdata: 用户调用 send 时传入的私有数据指针
 */
typedef void (*cmd_callback_t)(int ret_code, void *privdata);


// --- 接口函数 ---

/**
 * 初始化相机客户端
 * 注意：此函数只创建 Socket 并绑定到 EventLoop，不会立即发送数据。
 * * @param el:        已经创建好的 Redis aeEventLoop 指针
 * @param server_ip: 目标相机的 IP 地址 (如 "127.0.0.1")
 * @param port:      目标相机的端口 (如 14590)
 * @return:          成功返回客户端句柄指针，失败返回 NULL
 */
CameraClient* camera_client_init(aeEventLoop *el, const char *server_ip, int port);

/**
 * 异步发送控制命令
 * 此函数是非阻塞的，会立即返回。
 * 结果将在 aeMain 循环中通过 callback 通知。
 * * @param client:   由 camera_client_init 创建的句柄
 * @param method:   命令名称 (如 "start_video_recording")
 * @param cb:       命令完成或超时后的回调函数
 * @param privdata: 透传给回调函数的私有数据 (可为 NULL)
 * @return:         0 表示请求已入队，-1 表示参数错误或内存不足
 */
int camera_client_send(CameraClient *client, const char *method, cmd_callback_t cb, void *privdata);

/**
 * 销毁客户端
 * 释放 Socket、清理所有待处理的请求链表、移除 EventLoop 事件。
 * * @param client: 客户端句柄
 */
void camera_client_destroy(CameraClient *client);

#ifdef __cplusplus
}
#endif

#endif // CAMERA_CLIENT_ASYNC_H