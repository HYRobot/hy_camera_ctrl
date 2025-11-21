#ifndef GIMBAL_CTRL_H
#define GIMBAL_CTRL_H

#include "ae.h"
#include <stdint.h>
#include <unistd.h>

// 初始化云台 UART 端口
// @param uart_dev: 串口设备路径 (例如 "/dev/ttyS1")
// @return: 0 成功, -1 失败
int gimbal_ctrl_init(const char *uart_dev);

// 启动云台 UART 监听
// @param loop: ae 事件循环
// @return: 0 成功, -1 失败
int gimbal_ctrl_start(aeEventLoop *loop);

// 将 UDP 收到的 Mavlink 数据透传给云台 UART
// @param packet: Mavlink 消息的原始字节流
// @param len: 字节流长度
// @return: 实际写入的字节数
ssize_t gimbal_ctrl_forward_mavlink(const uint8_t *packet, size_t len);

// 停止并清理资源
void gimbal_ctrl_cleanup(aeEventLoop *loop);

#endif // GIMBAL_CTRL_H