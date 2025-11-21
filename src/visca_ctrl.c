#include "visca_ctrl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <mavlink.h>

static VISCAInterface_t iface;
static VISCACamera_t camera;

// 定义一些常量
#define ZOOM_MAX_VALUE 31424
#define FOCUS_MAX_VALUE 32768

int visca_ctrl_init(const char *device_path)
{
	if (VISCA_open_serial(&iface, device_path) != VISCA_SUCCESS) {
		fprintf(stderr, "visca_ctrl: unable to open serial device %s\n", device_path);
		return -1;
	}

	memset(&camera, 0, sizeof(VISCACamera_t));
	iface.broadcast = 0;
	camera.address = 1;

	// 可以在这里做一些相机初始化，比如清除 buffer
	VISCA_usleep(2000);

	// 默认设置
	VISCA_set_focus_auto(&iface, &camera, 2); // Auto focus on

	printf("VISCA interface initialized on %s\n", device_path);
	return 0;
}

void visca_ctrl_close()
{
	VISCA_close_serial(&iface);
}

void visca_ctrl_set_mipi(int on)
{
	if (on) {
		printf("Executing: MIPI On (0x0D)\n");
		VISCA_set_register(&iface, &camera, 0x72, 0x0D);
	} else {
		printf("Executing: MIPI Off (0x3F)\n");
		VISCA_set_register(&iface, &camera, 0x72, 0x3f);
	}
}

void visca_ctrl_process_command(uint8_t fun_type, uint8_t cmd_status)
{
	switch (fun_type) {
	case CAMERA_ZOOM: /* Camera zoom times. | */
		//printf("Set Zoom Value: %d\n", cmd_status);
		VISCA_set_zoom_value(&iface, &camera, (uint32_t)cmd_status * ZOOM_MAX_VALUE / 255);
		break;
	case CAMERA_IMAGE_FLIP: /* Camera image flig. | */
		if (cmd_status == OPEN_CMD)
		{
			VISCA_set_flip_value(&iface, &camera, 0x03);
		} else {
			VISCA_set_flip_value(&iface, &camera, 0x00);
		}
		break;
	case CAMERA_OSD_MODE: /* Camera OSD display. | */

		break;
	case CAMERA_TRACKER_MODE: /* Camera tracking switch. | */

		break;
	case CAMERA_FOCUS: /* Camera focus . | */
		VISCA_set_focus_auto(&iface, &camera, 3); //auto focus off
		VISCA_set_focus_value(&iface, &camera, (uint32_t)cmd_status * FOCUS_MAX_VALUE / 255);
		break;
	case CAMERA_APERTURE: /* Camera aperture. | */
		VISCA_set_auto_exp_mode(&iface, &camera, 3); //manual mode
		VISCA_set_iris_value(&iface, &camera, (uint32_t)(cmd_status & 0x11));
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

