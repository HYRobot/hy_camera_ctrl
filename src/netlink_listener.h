#ifndef NETLINK_LISTENER_H
#define NETLINK_LISTENER_H

#include "ae.h"

// 启动 Netlink 监听
// 成功返回 fd，失败返回 -1
int start_netlink_listener(aeEventLoop *el);

#endif