/*
 * Command line interface to the VISCA(tm) Camera Control Library
 * based on the VISCA(tm) Camera Control Library Test Program
 * by Damien Douxchamps
 *
 * Copyright (C) 2003 Simon Bichler
 *
 * Written by Simon Bichler <bichlesi@in.tum.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "libvisca.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h> /* File control definitions */
#include <errno.h> /* Error number definitions */
#include <string.h>
#include <linux/netlink.h>
#include <sys/socket.h>
#include <unistd.h>
#include "ae.h"
#include <mavlink.h>
#include <arpa/inet.h>
#include <cjson/cJSON.h>
#include "camera_client_async.h"

#define NETLINK_VISCA 31
#define MAX_PAYLOAD 32

#define DEBUG 0

const char *ttydev = "/dev/ttyS1";

/*Structures needed for the VISCA library*/
static VISCAInterface_t iface;
static VISCACamera_t camera;

static int mavlink_udp_fd;
static struct sockaddr_in client_udp_addr;
static socklen_t client_addrlen = sizeof(client_udp_addr);

void open_interface()
{
	//int camera_num;
	if (VISCA_open_serial(&iface, ttydev) != VISCA_SUCCESS) {
		fprintf(stderr, "hy_camera_ctrl: unable to open serial device %s\n", ttydev);
		exit(1);
	}
	memset(&camera, 0, sizeof(VISCACamera_t));
	iface.broadcast = 0;
#if 0
  VISCA_set_address(&iface, &camera_num);
  if(VISCA_set_address(&iface, &camera_num)!=VISCA_SUCCESS) {
#ifdef WIN
    _RPTF0(_CRT_WARN,"unable to set address\n");
#endif
    fprintf(stderr,"hy_camera_ctrl: unable to set address\n");xx
    VISCA_close_serial(&iface);
    exit(1);
  }
#endif
	camera.address = 1;

#if 0
	if (VISCA_clear(&iface, &camera) != VISCA_SUCCESS) {
		fprintf(stderr, "hy_camera_ctrl: unable to clear interface\n");
		VISCA_close_serial(&iface);
		exit(1);
	}
	if (VISCA_get_camera_info(&iface, &camera) != VISCA_SUCCESS) {
		fprintf(stderr, "hy_camera_ctrl: unable to oget camera infos\n");
		VISCA_close_serial(&iface);
		exit(1);
	}
	printf("Camera info: vendor=0x%02x model=0x%02x rom_version=0x%02x socket_num=%d\n",
	       camera.vendor, camera.model, camera.rom_version, camera.socket_num);
#endif
#if DEBUG
	fprintf(stderr, "Camera initialisation successful.\n");
#endif
}

void close_interface()
{
	// read the rest of the data: (should be empty)
	unsigned char packet[3000];
	uint32_t buffer_size = 3000;

	VISCA_usleep(2000);

	if (VISCA_unread_bytes(&iface, packet, &buffer_size) != VISCA_SUCCESS) {
		uint32_t i;
		fprintf(stderr, "ERROR: %u bytes not processed", buffer_size);
		for (i = 0; i < buffer_size; i++)
			fprintf(stderr, "%2x ", packet[i]);
		fprintf(stderr, "\n");
	}

	VISCA_close_serial(&iface);
}

// 回调函数，处理 Netlink 消息
void netlink_read_cb(struct aeEventLoop *el, int fd, void *clientData, int mask)
{
	struct nlmsghdr *nlh = (struct nlmsghdr*) malloc(NLMSG_SPACE(MAX_PAYLOAD));

	if (!nlh)
		return;

	struct iovec iov = { .iov_base = nlh, .iov_len = NLMSG_SPACE(MAX_PAYLOAD) };
	struct sockaddr_nl sa;
	struct msghdr msg = { .msg_name = &sa,
			      .msg_namelen = sizeof(sa),
			      .msg_iov = &iov,
			      .msg_iovlen = 1,
			      .msg_control = NULL,
			      .msg_controllen = 0,
			      .msg_flags = 0 };

	ssize_t len = recvmsg(fd, &msg, 0);
	if (len < 0) {
		perror("recvmsg");
		free(nlh);
		return;
	}

	int data_len = nlh->nlmsg_len - NLMSG_HDRLEN;
	
	#if DEBUG
	unsigned char *data = NLMSG_DATA(nlh);
	printf("Netlink message received: ");
	for (int i = 0; i < data_len; i++)
		printf("%02X ", data[i]);
	printf("\n");
	#endif

	if (data_len == 1) {
		if (((unsigned char *)NLMSG_DATA(nlh))[0] == 0x01) // MIPI On command
		{
			printf("Received MIPI on command 0x0E\n");
			//if (VISCA_set_register(&iface, &camera, 0x72, 0x02) != VISCA_SUCCESS) {
			if (VISCA_set_register(&iface, &camera, 0x72, 0x0D) != VISCA_SUCCESS) {
				printf("Failed to register MIPI on\n");
			}
		} else if (((unsigned char *)NLMSG_DATA(nlh))[0] == 0x0) // MIPI Off command
		{
			printf("Received MIPI Off command\n");
			if (VISCA_set_register(&iface, &camera, 0x72, 0x3f) != VISCA_SUCCESS) {
				printf("Failed to register MIPI off\n");
			}
		} else {
			printf("Unknown command received\n");
		}
	}

	free(nlh);
}

#define ZOOM_MAX_VALUE 31424 	//16385 : 光学变焦最大值, 31425:数字变焦最大值
#define FOCUS_MAX_VALUE 32768	//32768 : 对焦最大值

static void Process_camera_command(u_int8_t fun_type, u_int8_t cmd_status){
	uint16_t temp_val;
	uint32_t ret;
	switch (fun_type)
	{
	case CAMERA_ZOOM: /* Camera zoom times. | */
		//printf("Set Zoom Value: %d\n", cmd_status);
		VISCA_set_zoom_value(&iface, &camera, (uint32_t)cmd_status * ZOOM_MAX_VALUE / 255);
		break;
	case CAMERA_IMAGE_FLIP: /* Camera image flig. | */
		break;
	case CAMERA_OSD_MODE: /* Camera OSD display. | */
		ret = VISCA_get_focus_value(&iface, &camera, &temp_val);
		printf("ret = %d, Get Focus Value: %d\n", ret, temp_val);
		break;
	case CAMERA_TRACKER_MODE: /* Camera tracking switch. | */
		
		break;
	case CAMERA_FOCUS: /* Camera focus . | */
		VISCA_set_focus_auto(&iface, &camera, 3); //auto focus off
		VISCA_set_focus_value(&iface, &camera, (uint32_t)cmd_status * FOCUS_MAX_VALUE / 255);
		break;
	case CAMERA_APERTURE: /* Camera aperture. | */
		VISCA_set_focus_far(&iface, &camera);
		break;
    case CAMERA_TAKE_PHOTO: /* Camera captrue. | */
		VISCA_set_focus_near(&iface, &camera);
		break;
    case CAMERA_VIDEO_RECORD: /* Camera video record. | */
		break;
	default:
		break;
	}
}

/* UDP 回调 */
static void udp_read_cb(struct aeEventLoop *loop, int fd, void *data, int mask)
{
	uint8_t buf[256];
	int n = recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr *)&client_udp_addr, &client_addrlen);
	if (n <= 0)
		return;

#if DEBUG
	printf("UDP data received (%d bytes): ", n);
	for (int i = 0; i < n; i++)
		printf("%02X ", buf[i]);
	printf("\n");
#endif

	mavlink_message_t msg;
	mavlink_status_t status;
	for (int i = 0; i < n; i++) {
		if (mavlink_parse_char(MAVLINK_COMM_0, buf[i], &msg, &status)) {
			printf("MAVLink msgid=%u\n", msg.msgid);
			switch (msg.msgid) {
			case MAVLINK_MSG_ID_DATA16: {
				uint8_t type = mavlink_msg_data16_get_type(&msg);
				uint8_t len = mavlink_msg_data16_get_len(&msg);
				uint8_t data[16];
				mavlink_msg_data16_get_data(&msg, data);
				printf("Received DATA16: type=%u, len=%u, data=", type, len);
				for (int j = 0; j < len && j < 16; j++)
					printf("%02X ", data[j]);
				printf("\n");
				// Process DATA16 message
				break;
			}
			case MAVLINK_MSG_ID_DATA32: {
				uint8_t type = mavlink_msg_data32_get_type(&msg);
				uint8_t len = mavlink_msg_data32_get_len(&msg);
				uint8_t data[32];
				mavlink_msg_data32_get_data(&msg, data);
				printf("Received DATA32: type=%u, len=%u, data=", type, len);
				for (int j = 0; j < len && j < 32; j++)
					printf("%02X ", data[j]);
				printf("\n");
				// Process DATA32 message
				break;
			}
			case MAVLINK_MSG_ID_DATA64: {
				uint8_t type = mavlink_msg_data64_get_type(&msg);
				uint8_t len = mavlink_msg_data64_get_len(&msg);
				uint8_t data[64];
				mavlink_msg_data64_get_data(&msg, data);
				printf("Received DATA64: type=%u, len=%u, data=", type, len);
				for (int j = 0; j < len && j < 64; j++)
					printf("%02X ", data[j]);
				printf("\n");
				// Process DATA64 message
				break;
			}
			case MAVLINK_MSG_ID_GIMBAL_MANAGER_SET_MANUAL_CONTROL:
			case MAVLINK_MSG_ID_GIMBAL_MANAGER_SET_PITCHYAW:
			case MAVLINK_MSG_ID_HY_GIMBAL_CALIBRATION:
			case MAVLINK_MSG_ID_HY_GIMBAL_CHANNEL_CONFIG:
			case MAVLINK_MSG_ID_HY_GIMBAL_CONTROL:
			case MAVLINK_MSG_ID_HY_GIMBAL_DATA:
			case MAVLINK_MSG_ID_HY_GIMBAL_REPORT:
			case MAVLINK_MSG_ID_HY_REQUEST:
			case MAVLINK_MSG_ID_HY_VERSION:
				/* Forward to uart5 */
				printf("Forward HY_GIMBAL_CALIBRATION to GIMBAL\n");
				break;
			case MAVLINK_MSG_ID_HY_GIMBAL_CAMERA: {
				uint8_t fun_type = mavlink_msg_hy_gimbal_camera_get_fun_type(&msg);
				uint8_t cmd_status = mavlink_msg_hy_gimbal_camera_get_cmd_status(&msg);
				printf("Received HY_GIMBAL_CAMERAxx: fun_type=%u, cmd_status=%u\n", fun_type, cmd_status);
				// Process camera command
				Process_camera_command(fun_type, cmd_status);
				break;
			}
			default:
				break;
			}
		}
	}
}

int main(int argc, char **argv)
{
	struct aeEventLoop *loop = aeCreateEventLoop(1024);
	if (!loop) {
		printf("Failed to create event loop\n");
		return -1;
	}

	open_interface();

	// 1. 初始化 (只做一次)
    CameraClient *cam = camera_client_init(loop, "127.0.0.1", 14590);

	// 设置Netlink套接字，用于接收内核发来的VISCA命令
	struct sockaddr_nl src_addr;
	int netlinksock_fd;
	int group = 1;
	netlinksock_fd = socket(PF_NETLINK, SOCK_RAW, NETLINK_VISCA);
	if (netlinksock_fd < 0)
		return -1;

	memset(&src_addr, 0, sizeof(src_addr));
	src_addr.nl_family = AF_NETLINK;
	src_addr.nl_pid = 0;  // 让内核自动分配 PID
	bind(netlinksock_fd, (struct sockaddr *)&src_addr, sizeof(src_addr));

	// 订阅组 1
	setsockopt(netlinksock_fd, SOL_NETLINK, NETLINK_ADD_MEMBERSHIP, &group, sizeof(group));

	if (aeCreateFileEvent(loop, netlinksock_fd, AE_READABLE, netlink_read_cb, NULL) == AE_OK)
		printf("NETLink UDP event registered\n");
	else
		printf("Failed to register UDP event\n");

	// Setup UDP socket
	mavlink_udp_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (mavlink_udp_fd < 0) {
		perror("socket");
		return -1;
	}

	struct sockaddr_in udp_bind_addr;
	memset(&udp_bind_addr, 0, sizeof(udp_bind_addr));

	udp_bind_addr.sin_family = AF_INET;
	udp_bind_addr.sin_port = htons(4000);

	if (inet_pton(AF_INET, "127.0.0.1", &udp_bind_addr.sin_addr) <= 0) {
		perror("inet_pton");
		return -1;
	}

	if (bind(mavlink_udp_fd, (struct sockaddr *)&udp_bind_addr, sizeof(udp_bind_addr)) < 0) {
		perror("bind");
		return -1;
	}

	if (aeCreateFileEvent(loop, mavlink_udp_fd, AE_READABLE, udp_read_cb, NULL) == AE_OK)
		printf("MAVLink UDP event registered\n");
	else
		printf("Failed to register UDP event\n");


	VISCA_set_focus_auto(&iface, &camera, 2); //相机开机默认设置为 auto focus on

	aeMain(loop);
	close(netlinksock_fd);
	close(mavlink_udp_fd);
	close_interface();
	return 0;
}
