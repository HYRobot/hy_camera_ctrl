#include "gimbal_ctrl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <mavlink.h>
#include <sys/socket.h>
#include "mavlink_listener.h"
// --- 模块私有状态 ---
static int g_uart_fd = -1;

// --- 内部辅助函数 ---

// 配置 UART 端口
static int set_uart_config(int fd)
{
	struct termios tio;
	memset(&tio, 0, sizeof(tio));
	cfmakeraw(&tio); // 原始模式

	// 配置波特率和数据位 (假设 115200, 8N1)
	tio.c_cflag = B921600 | CS8 | CLOCAL | CREAD;
	tio.c_iflag = IGNPAR;
	tio.c_oflag = 0;
	tio.c_lflag = 0;

	tcflush(fd, TCIFLUSH);
	return (tcsetattr(fd, TCSANOW, &tio) < 0) ? -1 : 0;
}

// UART 读取回调：解析 Mavlink 并转发到 UDP
static void gimbal_uart_read_cb(struct aeEventLoop *loop, int fd, void *data, int mask)
{
	uint8_t rx_buf[256];
	int n = read(fd, rx_buf, sizeof(rx_buf));
	if (n <= 0)
		return;

	// Mavlink 协议解析状态机
	mavlink_message_t msg;
	mavlink_status_t status;

	for (int i = 0; i < n; i++) {
		// 使用 mavlink_parse_char 进行解析
		if (mavlink_parse_char(MAVLINK_COMM_0, rx_buf[i], &msg, &status)) {
			// 收到完整的 Mavlink 消息，准备转发

			uint8_t tx_buf[MAVLINK_MAX_PACKET_LEN];
			uint16_t tx_len;

			// 将 Mavlink 消息结构体编码回原始字节流
			tx_len = mavlink_msg_to_send_buffer(tx_buf, &msg);

			if (tx_len > 0) {
				// 将原始字节流透传给 UDP 客户端
				mavlink_clients_send_to_all(tx_buf, tx_len);
				printf("[Gimbal] UART -> UDP: Forwarded msg ID %u, len %d\n", msg.msgid, tx_len);
			}
		}
	}
}

// --- 公共 API 实现 ---

int gimbal_ctrl_init(const char *uart_dev)
{
	// 1. 打开串口
	g_uart_fd = open(uart_dev, O_RDWR | O_NOCTTY | O_NONBLOCK);
	if (g_uart_fd < 0) {
		perror("gimbal: uart open failed");
		return -1;
	}

	// 2. 配置串口参数
	if (set_uart_config(g_uart_fd) < 0) {
		perror("gimbal: uart config failed");
		close(g_uart_fd);
		g_uart_fd = -1;
		return -1;
	}

	printf("Gimbal UART initialized on %s\n", uart_dev);
	return 0;
}

int gimbal_ctrl_start(aeEventLoop *loop)
{
	if (g_uart_fd < 0)
		return -1;

	// 注册 UART 读事件
	if (aeCreateFileEvent(loop, g_uart_fd, AE_READABLE, gimbal_uart_read_cb, NULL) == AE_ERR) {
		printf("gimbal: Failed to register UART event\n");
		return -1;
	}

	printf("Gimbal UART listener started.\n");
	return 0;
}

ssize_t gimbal_ctrl_forward_mavlink(const uint8_t *packet, size_t len)
{
	if (g_uart_fd < 0)
		return -1;

	// UDP -> UART 透传
	ssize_t written = write(g_uart_fd, packet, len);

    #if 1
	if (written == len) {
		printf("[Gimbal] UDP -> UART: Forwarded %zu bytes\n", len);
		for (size_t i = 0; i < len; i++) {
			printf("%02X ", packet[i]);
		}
		printf("\n");
	} else {
		perror("gimbal: uart write failed");
	}
    #endif

	return written;
}

void gimbal_ctrl_cleanup(aeEventLoop *loop)
{
	if (g_uart_fd >= 0) {
		// 移除事件
		if (loop)
			aeDeleteFileEvent(loop, g_uart_fd, AE_READABLE);
		// 关闭串口
		close(g_uart_fd);
		g_uart_fd = -1;
	}
}