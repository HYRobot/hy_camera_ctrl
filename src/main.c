#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ae.h"
#include "visca_ctrl.h"
#include "netlink_listener.h"
#include "mavlink_listener.h"
#include "camera_client_async.h"
#include "liangyuan_lrf_905.h"
#include "gimbal_ctrl.h"

#define VISCA_CAM_DEV "/dev/ttyS1"
#define LRF_UART_DEV "/dev/ttyS3"
#define GIMBAL_UART_DEV "/dev/ttyS5"
#define GPIO_CHIP_DEV "/dev/gpiochip1"
#define GPIO_LINE_NUM 18

int main(int argc, char **argv) {
    // 1. 创建事件循环
    struct aeEventLoop *loop = aeCreateEventLoop(1024);
    if (!loop) {
        fprintf(stderr, "Failed to create event loop\n");
        return 1;
    }

    // 2. 初始化 LRF 模块 (GPIO 上电 + UART 打开)
    if (lrf_init(LRF_UART_DEV, GPIO_CHIP_DEV, GPIO_LINE_NUM) < 0) {
        fprintf(stderr, "LRF Init failed\n");
        // 根据需求决定是退出还是继续运行其他模块
        // return -1; 
    }

    // 3. 初始化 VISCA 硬件控制层
    if (visca_ctrl_init(VISCA_CAM_DEV) != 0) {
        // 根据需求，硬件初始化失败是否要退出程序？
        fprintf(stderr, "Warning: VISCA Init failed, proceeding anyway...\n");
    }

    // 1. 初始化云台控制
    if (gimbal_ctrl_init(GIMBAL_UART_DEV) < 0) { 
        fprintf(stderr, "Gimbal Init failed.\n");
    }

    // 4. 初始化异步相机客户端 (用于发送 start_video_recording 等)
    CameraClient *cam_client = camera_client_init(loop, "127.0.0.1", 14590);
    if (!cam_client) {
        fprintf(stderr, "Failed to init camera client\n");
    }

    // 5. 启动 Netlink 监听 (内核事件 -> VISCA)
    int netlink_fd = start_netlink_listener(loop);
    if (netlink_fd < 0) {
        fprintf(stderr, "Failed to start Netlink listener\n");
    }

    // 6. 启动 Mavlink 监听 (UDP -> VISCA)
    int mavlink_fd = start_mavlink_listener(loop, "0.0.0.0", 3000);
    if (mavlink_fd < 0) {
        fprintf(stderr, "Failed to start Mavlink listener\n");
    }

    // 2. 启动云台监听
    // 注意：gimbal_ctrl_start 需要一个初始回复地址。
    if (gimbal_ctrl_start(loop) < 0) {
         fprintf(stderr, "Gimbal Start failed.\n");
    }

    // 7. 启动 LRF 监听 (把 UART fd 加入 loop)
    if (lrf_start(loop, cam_client) == 0) {
        printf("LRF Module Started.\n");
        
        // 等待硬件稳定后，发送开始指令
        sleep(1); 
        lrf_cmd_continuous(4); // 4Hz
    }

    printf("Service started. Waiting for events...\n");

    // 8. 进入主循环
    aeMain(loop);

    // 9. 清理资源 (如果 aeMain 退出)
    gimbal_ctrl_cleanup(loop);
    lrf_cleanup(loop);
    aeDeleteEventLoop(loop);
    if (cam_client) camera_client_destroy(cam_client);
    visca_ctrl_close();
    
    return 0;
}