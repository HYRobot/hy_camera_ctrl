#ifndef VISCA_CTRL_H
#define VISCA_CTRL_H

#include "libvisca.h"
#include <stdint.h>

// 初始化串口和相机
int visca_ctrl_init(const char *device_path);

// 关闭
void visca_ctrl_close();

// 设置 MIPI 状态 (给 Netlink 模块用)
void visca_ctrl_set_mipi(int on);

// 处理 Mavlink 传来的通用命令 (给 Mavlink 模块用)
// fun_type 和 cmd_status 来自 mavlink 消息
void visca_ctrl_process_command(uint8_t fun_type, uint8_t cmd_status);

#endif