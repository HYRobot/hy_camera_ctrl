#ifndef MAVLINK_LISTENER_H
#define MAVLINK_LISTENER_H

#include "ae.h"
#include <sys/socket.h>
#include <netinet/in.h>

// 添加：管理并向所有已知 UDP 客户端发送数据的接口
int mavlink_clients_add(const struct sockaddr_in *addr);
int mavlink_clients_remove(const struct sockaddr_in *addr);
void mavlink_clients_clear(void);
/* 将 buf 原样发送给所有已知客户端，返回成功发送的客户端数量（>=0），或 -1 出错 */
int mavlink_clients_send_to_all(const uint8_t *buf, size_t len);
/* 返回当前 mavlink UDP socket fd（或 -1）*/
int mavlink_get_udp_fd(void);

// 启动 Mavlink UDP 监听
// 成功返回 fd，失败返回 -1
int start_mavlink_listener(aeEventLoop *el, const char *ip, int port);

#endif