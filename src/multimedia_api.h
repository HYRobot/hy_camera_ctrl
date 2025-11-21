#ifndef MULTIMEDIA_API_H__
#define MULTIMEDIA_API_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    ERROR_SUCCESS = 0,
    ERROR_GENERAL = -1,
    ERROR_INVALID_PARAMETER = -2,
    ERROR_NOT_SUPPORTED = -3,
    ERROR_OUT_OF_MEMORY = -4,
    ERROR_IO = -5,
    ERROR_TIMEOUT = -6,
    ERROR_NO_SD = -7,
    ERROR_REQUEST_FAILED = -8,
} error_code_t;

typedef enum {
    RESOLUTION_UNKNOWN = -1,
    RESOLUTION_4K = 0,
    RESOLUTION_1080P = 1,
    RESOLUTION_720P = 2,
    RESOLUTION_480P = 3,
} resolution_t;

typedef enum {
    VIDEO_TYPE_VISION = 0x01,
    VIDEO_TYPE_INFRARED = 0x02,
} video_type_t;

extern error_code_t init_multimedia_api();
extern error_code_t deinit_multimedia_api();
// 拍照录像接口，照片和视频保存在sdcard中，如果没有sdcard则返回错误
extern error_code_t take_photo(int timeout_ms);
extern error_code_t start_video_recording(int timeout_ms);
extern error_code_t stop_video_recording(int timeout_ms);
extern error_code_t get_recording_status(bool* is_recording, int timeout_ms);

// 录像分辨率设置，只针对可见光视频流
extern error_code_t set_recording_resolution(resolution_t resolution, int timeout_ms);
extern error_code_t get_recording_resolution(resolution_t* resolution, int timeout_ms);

// 预览分辨率设置，只针对可见光视频流
extern error_code_t set_preview_resolution(resolution_t resolution, int timeout_ms);
extern error_code_t get_preview_resolution(resolution_t* resolution, int timeout_ms);

// OSD 显示，增加或更新OSD 显示，OSD 叠加到指定的视频类型， index 为 OSD 索引，范围为 [0, 16], x,y 为 OSD 位置，范围为 [0, 100]，表示所占图像的百分比， font_color 为 ARGB 格式
extern error_code_t add_osd_display(video_type_t type, int index, int x, int y, int font_size, int font_color, const char* text, int timeout_ms);
// 删除OSD 显示，OSD 叠加到指定的视频类型， index 为 OSD 索引，当 index 为 -1 时，删除所有 OSD 显示
extern error_code_t remove_osd_display(video_type_t type, int index, int timeout_ms);

// 识别和扫描视频中的物体
extern error_code_t start_scanning(video_type_t type, int timeout_ms);
extern error_code_t stop_scanning(video_type_t type, int timeout_ms);
extern error_code_t is_scanning(video_type_t type, bool* is_scanning, int timeout_ms);

// 坐标和尺寸范围为 [0, 100]，表示所占图像的百分比
extern error_code_t start_tracking(video_type_t type, float x, float y, float width, float height, int timeout_ms);
extern error_code_t stop_tracking(video_type_t type, int timeout_ms);
extern error_code_t is_tracking(video_type_t type, bool* is_tracking, int timeout_ms);

// sdcard 状态查询接口，返回 sdcard 是否插入、总容量、可用容量、已用容量等信息。 
extern error_code_t get_sdcard_status(bool* is_inserted, uint64_t* total_capacity_mb, uint64_t* available_capacity_mb, uint64_t* used_capacity_mb, int timeout_ms);
extern error_code_t format_sdcard(int timeout_ms);

#ifdef __cplusplus
}
#endif

#endif