#include "liangyuan_lrf_905.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <errno.h>
#include <gpiod.h>
#include <mavlink.h>

// --- 宏定义 ---
#define LRF_STX 0x55
#define LRF_CMD_STANDBY 0x00
#define LRF_CMD_SINGLE 0x01
#define LRF_CMD_CONTINUOUS 0x02
#define LRF_CMD_GET_VERSION 0xCB
#define LRF_RSP_VERSION_ALT 0xBB

#define UART_BUF_SIZE 64

// --- 内部状态结构 ---
enum lrf_state {
    STATE_WAIT_STX = 0,
    STATE_GOT_STX,
    STATE_GOT_CMD,
    STATE_GOT_LEN,
    STATE_GOT_DATA,
};

struct lrf905 {
    enum lrf_state rx_state;
    uint8_t cmd;
    uint8_t len;
    uint8_t buf[UART_BUF_SIZE];
    uint8_t idx;
    uint8_t xor_sum;
};

// --- 静态变量 (模块私有) ---
static int g_uart_fd = -1;
static struct gpiod_chip *gpio_chip_handle = NULL;
static struct gpiod_line *gpio_line_handle = NULL;

static struct lrf905 slrf;

// 用于发送数据的
static struct CameraClient *g_camera_client = NULL;

// --- 内部辅助函数 ---

static inline uint8_t lrf_xor(const uint8_t *b, int n) {
    uint8_t x = 0;
    for (int i = 0; i < n; i++) x ^= b[i];
    return x;
}

static int lrf_send_frame(uint8_t cmd, uint8_t len, uint8_t dH, uint8_t dL) {
    if (g_uart_fd < 0) return -1;
    
    uint8_t frame[6];
    frame[0] = LRF_STX;
    frame[1] = cmd;
    frame[2] = len;
    frame[3] = dH;
    frame[4] = dL;
    frame[5] = lrf_xor(frame, 5);

    int ret = write(g_uart_fd, frame, 6);
    return (ret == 6) ? 0 : -1;
}

static void lrf_handle_ranging(const uint8_t *data, uint8_t len) {
    if (len != 10 || g_camera_client == NULL) return;

    uint32_t head = (data[1] << 16) | (data[2] << 8) | data[3]; // 首目标距离

    //mavlink_message_t message;
    //mavlink_hy_laser_ranging_t hy_laser_ranging;
    //hy_laser_ranging.distance = (float)head / 10.0f; // 精度 0.1m

    //mavlink_msg_hy_laser_ranging_encode(1, 200, &message, &hy_laser_ranging);
    //uint16_t buflen = mavlink_msg_to_send_buffer((uint8_t *)buf, &message);

    //g_camera_client
    //camera_client_send(g_camera_client, "start_video_recording", my_cb, "Task1");
    

    //printf("[LRF] Dist: %.2f m (sent via UDP)\n", (float)head / 10.0f);
}

static void lrf_rx_frame_done(uint8_t cmd, uint8_t len, const uint8_t *pl) {
    switch (cmd) {
    case LRF_CMD_SINGLE:
    case LRF_CMD_CONTINUOUS:
        lrf_handle_ranging(pl, len);
        break;
    default:
        break;
    }
}

// --- 回调函数 ---

static void uart_read_cb(struct aeEventLoop *loop, int fd, void *data, int mask) {
    uint8_t buf[UART_BUF_SIZE];
    int n = read(fd, buf, UART_BUF_SIZE);
    if (n <= 0) return;

    for (int i = 0; i < n; i++) {
        uint8_t b = buf[i];
        switch (slrf.rx_state) {
        case STATE_WAIT_STX:
            if (b == LRF_STX) {
                slrf.rx_state = STATE_GOT_STX;
                slrf.xor_sum = b;
            }
            break;
        case STATE_GOT_STX:
            slrf.cmd = b;
            slrf.xor_sum ^= b;
            slrf.rx_state = STATE_GOT_CMD;
            break;
        case STATE_GOT_CMD:
            slrf.len = b;
            slrf.xor_sum ^= b;
            slrf.idx = 0;
            if (slrf.len > sizeof(slrf.buf)) slrf.rx_state = STATE_WAIT_STX;
            else if (slrf.len == 0) slrf.rx_state = STATE_GOT_DATA;
            else slrf.rx_state = STATE_GOT_LEN;
            break;
        case STATE_GOT_LEN:
            slrf.buf[slrf.idx++] = b;
            slrf.xor_sum ^= b;
            if (slrf.idx >= slrf.len) slrf.rx_state = STATE_GOT_DATA;
            break;
        case STATE_GOT_DATA:
            if (slrf.xor_sum == b)
                lrf_rx_frame_done(slrf.cmd, slrf.len, slrf.buf);
            slrf.rx_state = STATE_WAIT_STX;
            break;
        }
    }
}

// --- 公共 API 实现 ---

int lrf_init(const char *uart_dev, const char *gpio_chip, int gpio_line) {
    // 1. GPIO 初始化 (Power On)
    gpio_chip_handle = gpiod_chip_open(gpio_chip);
    if (!gpio_chip_handle) {
        perror("lrf: gpio open failed");
        return -1;
    }
    gpio_line_handle = gpiod_chip_get_line(gpio_chip_handle, gpio_line);
    if (!gpio_line_handle) {
        perror("lrf: gpio get line failed");
        return -1;
    }
    if (gpiod_line_request_output(gpio_line_handle, "lrf_power", 0) < 0) {
        perror("lrf: gpio request output failed");
        return -1;
    }
    gpiod_line_set_value(gpio_line_handle, 1); // Set High
    printf("LRF Power ON (GPIO %d)\n", gpio_line);

    // 2. UART 初始化
    struct termios tio;
    g_uart_fd = open(uart_dev, O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (g_uart_fd < 0) {
        perror("lrf: uart open failed");
        return -1;
    }
    memset(&tio, 0, sizeof(tio));
    cfmakeraw(&tio);
    tio.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
    tio.c_iflag = IGNPAR;
    tcflush(g_uart_fd, TCIFLUSH);
    tcsetattr(g_uart_fd, TCSANOW, &tio);

    // 3. 状态机重置
    slrf.rx_state = STATE_WAIT_STX;

    return 0;
}

int lrf_start(aeEventLoop *loop, CameraClient *camera_client) {
    if (g_uart_fd < 0) return -1;

    if (camera_client != NULL) {
        g_camera_client = camera_client;
    }

    // 注册事件
    if (aeCreateFileEvent(loop, g_uart_fd, AE_READABLE, uart_read_cb, NULL) != AE_OK) {
        return -1;
    }
    
    return 0;
}

int lrf_cmd_continuous(uint8_t hz) {
    printf("LRF cmd continuous: %d Hz\n", hz);
    return lrf_send_frame(LRF_CMD_CONTINUOUS, 0x02, 0x20, hz);
}

int lrf_cmd_standby(void) {
    return lrf_send_frame(LRF_CMD_STANDBY, 0x02, 0x00, 0x00);
}

void lrf_cleanup(aeEventLoop *loop) {
    // 停止测量
    lrf_cmd_standby();
    
    // 移除事件
    if (loop && g_uart_fd >= 0) {
        aeDeleteFileEvent(loop, g_uart_fd, AE_READABLE);
    }

    // 关闭 UART
    if (g_uart_fd >= 0) {
        close(g_uart_fd);
        g_uart_fd = -1;
    }

    // GPIO Power Off
    if (gpio_line_handle) {
        gpiod_line_set_value(gpio_line_handle, 0); // Set Low
        gpiod_line_release(gpio_line_handle);
        gpio_line_handle = NULL;
    }
    if (gpio_chip_handle) {
        gpiod_chip_close(gpio_chip_handle);
        gpio_chip_handle = NULL;
    }
    printf("LRF Cleaned up.\n");
}