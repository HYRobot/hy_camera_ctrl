#ifndef LIANGYUAN_LRF_905_H
#define LIANGYUAN_LRF_905_H

#include "ae.h"
#include <stdint.h>
#include "camera_client_async.h"

// 初始化 LRF 模块 (GPIO 上电, UART 初始化)
// 返回 0 成功, -1 失败
int lrf_init(const char *uart_dev, const char *gpio_chip, int gpio_line);

// 启动 LRF 事件监听 (注册 UART 到 EventLoop)
// udp_fd: 用于发送测距结果的 UDP socket
// camera_client: 用于测距结果发送
int lrf_start(aeEventLoop *loop, CameraClient *camera_client);

// 发送开启连续测量指令
int lrf_cmd_continuous(uint8_t hz);

// 发送待机指令
int lrf_cmd_standby(void);

// 停止并清理资源 (关闭 UART, GPIO 下电, 释放内存)
void lrf_cleanup(aeEventLoop *loop);

#endif // LIANGYUAN_LRF_905_H