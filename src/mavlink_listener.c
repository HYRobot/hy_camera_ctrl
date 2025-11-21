#include "mavlink_listener.h"
#include "visca_ctrl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "gimbal_ctrl.h"
#include <mavlink.h> // 确保包含正确的 mavlink 头文件

// 新增：客户端列表管理
#define MAVLINK_MAX_CLIENTS 16
static struct sockaddr_in g_clients[MAVLINK_MAX_CLIENTS];
static int g_client_count = 0;
static int g_mavlink_fd = -1;

static int sockaddr_in_equal(const struct sockaddr_in *a, const struct sockaddr_in *b)
{
	return a->sin_family == b->sin_family && a->sin_addr.s_addr == b->sin_addr.s_addr && a->sin_port == b->sin_port;
}

int mavlink_clients_add(const struct sockaddr_in *addr)
{
	if (!addr)
		return -1;
	for (int i = 0; i < g_client_count; i++) {
		if (sockaddr_in_equal(&g_clients[i], addr))
			return 0; // 已存在
	}
	if (g_client_count >= MAVLINK_MAX_CLIENTS)
		return -1;
	g_clients[g_client_count++] = *addr;
	return 0;
}

int mavlink_clients_remove(const struct sockaddr_in *addr)
{
	if (!addr)
		return -1;
	for (int i = 0; i < g_client_count; i++) {
		if (sockaddr_in_equal(&g_clients[i], addr)) {
			g_clients[i] = g_clients[g_client_count - 1];
			g_client_count--;
			return 0;
		}
	}
	return -1;
}

void mavlink_clients_clear(void)
{
	g_client_count = 0;
}

int mavlink_clients_send_to_all(const uint8_t *buf, size_t len)
{
	if (g_mavlink_fd < 0)
		return -1;
	int sent_ok = 0;
	for (int i = 0; i < g_client_count; i++) {
		ssize_t s = sendto(g_mavlink_fd, buf, len, 0, (struct sockaddr *)&g_clients[i], sizeof(g_clients[i]));
		if (s == (ssize_t)len)
			sent_ok++;
		else {
			// 非致命，继续尝试其他客户端
		}
	}
	return sent_ok;
}

int mavlink_get_udp_fd(void)
{
	return g_mavlink_fd;
}

// udp_read_cb 中自动将发送方加入客户端列表
static void udp_read_cb(struct aeEventLoop *loop, int fd, void *data, int mask)
{
	uint8_t buf[256];
	struct sockaddr_in client_addr;
	socklen_t addr_len = sizeof(client_addr);

	int n = recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr *)&client_addr, &addr_len);
	if (n <= 0)
		return;

	// 新增：记录/更新客户端列表
	mavlink_clients_add(&client_addr);

	mavlink_message_t msg;
	mavlink_status_t status;

	for (int i = 0; i < n; i++) {
		if (mavlink_parse_char(MAVLINK_COMM_0, buf[i], &msg, &status)) {
			printf("MAVLink msgid=%u\n", msg.msgid);

			switch (msg.msgid) {
			case MAVLINK_MSG_ID_HY_GIMBAL_CAMERA: {
				uint8_t fun_type = mavlink_msg_hy_gimbal_camera_get_fun_type(&msg);
				uint8_t cmd_status = mavlink_msg_hy_gimbal_camera_get_cmd_status(&msg);

				printf("[Mavlink] Camera CMD: type=%u, val=%u\n", fun_type, cmd_status);
				visca_ctrl_process_command(fun_type, cmd_status);
				break;
			}
			default:
				// 将原始 UDP 消息体（Mavlink Packet）转发给云台 UART
				if (n > 0) {
					gimbal_ctrl_forward_mavlink(buf, n);
				}
				break;
			}
		}
	}
}

int start_mavlink_listener(aeEventLoop *el, const char *ip, int port)
{
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0) {
		perror("mavlink socket");
		return -1;
	}

	g_mavlink_fd = fd; // 保存 socket fd，供 send_to_all 使用

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	if (inet_pton(AF_INET, ip, &addr.sin_addr) <= 0) {
		perror("mavlink inet_pton");
		close(fd);
		g_mavlink_fd = -1;
		return -1;
	}

	if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("mavlink bind");
		close(fd);
		g_mavlink_fd = -1;
		return -1;
	}

	if (aeCreateFileEvent(el, fd, AE_READABLE, udp_read_cb, NULL) == AE_ERR) {
		printf("Failed to register mavlink event\n");
		close(fd);
		g_mavlink_fd = -1;
		return -1;
	}

	printf("Mavlink listener started on %s:%d (fd %d)\n", ip, port, fd);
	return fd;
}