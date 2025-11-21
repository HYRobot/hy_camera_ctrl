/** @file
 *  @brief MAVLink comm protocol generated from hy_gimbal.xml
 *  @see http://mavlink.org
 */
#pragma once
#ifndef MAVLINK_HY_GIMBAL_H
#define MAVLINK_HY_GIMBAL_H

#ifndef MAVLINK_H
    #error Wrong include order: MAVLINK_HY_GIMBAL.H MUST NOT BE DIRECTLY USED. Include mavlink.h from the same directory instead or set ALL AND EVERY defines from MAVLINK.H manually accordingly, including the #define MAVLINK_H call.
#endif

#define MAVLINK_HY_GIMBAL_XML_HASH 4292177395013691967

#ifdef __cplusplus
extern "C" {
#endif

// MESSAGE LENGTHS AND CRCS

#ifndef MAVLINK_MESSAGE_LENGTHS
#define MAVLINK_MESSAGE_LENGTHS {}
#endif

#ifndef MAVLINK_MESSAGE_CRCS
#define MAVLINK_MESSAGE_CRCS {{169, 234, 18, 18, 0, 0, 0}, {170, 73, 34, 34, 0, 0, 0}, {171, 181, 66, 66, 0, 0, 0}, {287, 1, 23, 23, 3, 20, 21}, {288, 20, 23, 23, 3, 20, 21}, {5002, 156, 50, 50, 0, 0, 0}, {11047, 74, 1, 1, 0, 0, 0}, {11048, 196, 2, 2, 0, 0, 0}, {11050, 217, 10, 10, 0, 0, 0}, {11051, 66, 2, 2, 0, 0, 0}, {11052, 130, 10, 10, 0, 0, 0}, {11053, 9, 16, 16, 0, 0, 0}, {11054, 133, 4, 4, 0, 0, 0}, {11060, 27, 2, 2, 0, 0, 0}}
#endif

#include "../protocol.h"

#define MAVLINK_ENABLED_HY_GIMBAL

// ENUM DEFINITIONS


/** @brief Flags for high level gimbal manager operation The first 16 bits are identical to the GIMBAL_DEVICE_FLAGS. */
#ifndef HAVE_ENUM_GIMBAL_MANAGER_FLAGS
#define HAVE_ENUM_GIMBAL_MANAGER_FLAGS
typedef enum GIMBAL_MANAGER_FLAGS
{
   GIMBAL_MANAGER_FLAGS_RETRACT=1, /* Based on GIMBAL_DEVICE_FLAGS_RETRACT. | */
   GIMBAL_MANAGER_FLAGS_NEUTRAL=2, /* Based on GIMBAL_DEVICE_FLAGS_NEUTRAL. | */
   GIMBAL_MANAGER_FLAGS_ROLL_LOCK=4, /* Based on GIMBAL_DEVICE_FLAGS_ROLL_LOCK. | */
   GIMBAL_MANAGER_FLAGS_PITCH_LOCK=8, /* Based on GIMBAL_DEVICE_FLAGS_PITCH_LOCK. | */
   GIMBAL_MANAGER_FLAGS_YAW_LOCK=16, /* Based on GIMBAL_DEVICE_FLAGS_YAW_LOCK. | */
   GIMBAL_MANAGER_FLAGS_YAW_IN_VEHICLE_FRAME=32, /* Based on GIMBAL_DEVICE_FLAGS_YAW_IN_VEHICLE_FRAME. | */
   GIMBAL_MANAGER_FLAGS_YAW_IN_EARTH_FRAME=64, /* Based on GIMBAL_DEVICE_FLAGS_YAW_IN_EARTH_FRAME. | */
   GIMBAL_MANAGER_FLAGS_ACCEPTS_YAW_IN_EARTH_FRAME=128, /* Based on GIMBAL_DEVICE_FLAGS_ACCEPTS_YAW_IN_EARTH_FRAME. | */
   GIMBAL_MANAGER_FLAGS_RC_EXCLUSIVE=256, /* Based on GIMBAL_DEVICE_FLAGS_RC_EXCLUSIVE. | */
   GIMBAL_MANAGER_FLAGS_RC_MIXED=512, /* Based on GIMBAL_DEVICE_FLAGS_RC_MIXED. | */
   GIMBAL_MANAGER_FLAGS_ENUM_END=513, /*  | */
} GIMBAL_MANAGER_FLAGS;
#endif

/** @brief  */
#ifndef HAVE_ENUM_MAV_STATUS_GIMBAL
#define HAVE_ENUM_MAV_STATUS_GIMBAL
typedef enum MAV_STATUS_GIMBAL
{
   MAV_MODE_GIMBAL_UNINITIALIZED=0, /* Gimbal is powered on but has not started initializing yet. | */
   MAV_MODE_GIMBAL_BOOTING=1, /* Gimbal is is booting up.. | */
   MAV_MODE_GIMBAL_STANDBY=2, /* Gimbal is standby, waiting for start. | */
   MAV_MODE_GIMBAL_ACTIVE_FOLLOW=3, /* Gimbal is actively stabilizing. | */
   MAV_MODE_GIMBAL_ACTIVE_GLOBAL=4, /* Gimbal is actively stabilizing. | */
   MAV_MODE_GIMBAL_CALIBRATING=5, /* Gimbal is currently running calibration on  axis. | */
   MAV_MODE_GIMBAL_CALIBRATION_FINISHED=6, /* Gimbal calibration is finished on axis. | */
   MAV_MODE_GIMBAL_NO_IMU=7, /* Gimbal has no imu detected. | */
   MAV_MODE_GIMBAL_NO_MAG_ROLL=8, /* Gimbal has no roll encoder detected. | */
   MAV_MODE_GIMBAL_NO_MAG_PITCH=9, /* Gimbal has no pitch encoder detected. | */
   MAV_MODE_GIMBAL_NO_MAG_YAW=10, /* Gimbal has no yaw encoder detected. | */
   GIMBAL_ROLL_CALIBRATION_REQUIRED=11, /* This roll axis need calibration. | */
   GIMBAL_PITCH_CALIBRATION_REQUIRED=12, /* This pitch axis haven't calibration. | */
   GIMBAL_YAW_CALIBRATION_REQUIRED=13, /* This yaw axis need calibration. | */
   MAV_STATUS_GIMBAL_ENUM_END=14, /*  | */
} MAV_STATUS_GIMBAL;
#endif

/** @brief  */
#ifndef HAVE_ENUM_GIMBAL_AXIS
#define HAVE_ENUM_GIMBAL_AXIS
typedef enum GIMBAL_AXIS
{
   GIMBAL_AXIS_PITCH=1, /* Gimbal yaw axis. | */
   GIMBAL_AXIS_ROLL=2, /* Gimbal pitch axis. | */
   GIMBAL_AXIS_YAW=3, /* Gimbal roll axis. | */
   GIMBAL_AXIS_ENUM_END=4, /*  | */
} GIMBAL_AXIS;
#endif

/** @brief  */
#ifndef HAVE_ENUM_GIMBAL_CALIBRATION_TYPE
#define HAVE_ENUM_GIMBAL_CALIBRATION_TYPE
typedef enum GIMBAL_CALIBRATION_TYPE
{
   GIMBAL_ZERO_POINT_CALIBRATION=1, /* encoder zero point calibration. | */
   GIMBAL_PREFRONT_POINT_CALIBRATION=2, /* encoder pre front point calibration. | */
   GIMBAL_FRONT_POINT_CALIBRATION=3, /* encoder front point calibration. | */
   GIMBAL_LINEAR_CALIBRATION=4, /* encoder linear calibration. | */
   GIMBAL_IMU_HEXAHEDRON_CALIBRATION=5, /* imu accelerometer six faces calibration. | */
   GIMBAL_IMU_TEMPERATURE_CALIBRATION=6, /* imu temperature calibration. | */
   GIMBAL_CALIBRATION_TYPE_ENUM_END=7, /*  | */
} GIMBAL_CALIBRATION_TYPE;
#endif

/** @brief  */
#ifndef HAVE_ENUM_GIMBAL_CHENNEL_TYPE
#define HAVE_ENUM_GIMBAL_CHENNEL_TYPE
typedef enum GIMBAL_CHENNEL_TYPE
{
   PITCH_FUNCTION=1, /* pitch control function. | */
   YAW_FUNCTION=2, /* yaw control function. | */
   PITCH_MODE_FUNCTION=3, /* pitch control mode function. | */
   YAW_MODE_FUNCTION=4, /* yaw control mode function. | */
   CAMERA_ZOOM_FUNCTION=5, /* camera zoom function for RC. | */
   TAKE_PHOTO_FUNCTION=6, /* take photo function for RC. | */
   VIDEO_RECORD_FUNCTION=7, /* video record function for RC. | */
   OBJECT_TRACKER_FUNCTION=8, /* object tracker function. | */
   GIMBAL_CHENNEL_TYPE_ENUM_END=9, /*  | */
} GIMBAL_CHENNEL_TYPE;
#endif

/** @brief  */
#ifndef HAVE_ENUM_REQUEST_CMD_TYPES
#define HAVE_ENUM_REQUEST_CMD_TYPES
typedef enum REQUEST_CMD_TYPES
{
   NONE_REQUEST=0, /* none clear request. | */
   CONNECT_REQUEST=1, /* connection request, used in uart and ethernet connect. | */
   UPGRADE_REQUEST=2, /* upgrade program request . | */
   VERSION_REQUEST=3, /* version request. | */
   CHANNEL_REQUEST=4, /* control channel request. | */
   REQUEST_CMD_TYPES_ENUM_END=5, /*  | */
} REQUEST_CMD_TYPES;
#endif

/** @brief  */
#ifndef HAVE_ENUM_CAMERA_FUNCTION_TYPE
#define HAVE_ENUM_CAMERA_FUNCTION_TYPE
typedef enum CAMERA_FUNCTION_TYPE
{
   CAMERA_HEARTBEAT_FUNCTION=0, /* Camera heartbeat, announce camera component ID at 1Hz. | */
   CAMERA_ZOOM=1, /* Camera zoom times. | */
   CAMERA_IMAGE_FLIP=2, /* Camera image flig. | */
   CAMERA_OSD_MODE=3, /* Camera OSD display. | */
   CAMERA_TRACKER_MODE=4, /* Camera tracking switch. | */
   CAMERA_FOCUS=5, /* Camera focus . | */
   CAMERA_APERTURE=6, /* Camera aperture. | */
   CAMERA_TAKE_PHOTO=7, /* Camera captrue. | */
   CAMERA_VIDEO_RECORD=8, /* Camera video record. | */
   CAMERA_FUNCTION_TYPE_ENUM_END=9, /*  | */
} CAMERA_FUNCTION_TYPE;
#endif

/** @brief  */
#ifndef HAVE_ENUM_CAMERA_CMD_STATUS
#define HAVE_ENUM_CAMERA_CMD_STATUS
typedef enum CAMERA_CMD_STATUS
{
   CAMERA_NONE=0, /* No camera command (idle state). | */
   OPEN_CMD=1, /* open operation. | */
   CLOSE_CMD=2, /* close operation. | */
   CAMERA_FEEDBACK_CLOSEDLOOP=3, /* Closed loop feedback , we know for sure it has successfully taken a operation. | */
   CAMERA_CMD_STATUS_ENUM_END=4, /*  | */
} CAMERA_CMD_STATUS;
#endif

// MAVLINK VERSION

#ifndef MAVLINK_VERSION
#define MAVLINK_VERSION 3
#endif

#if (MAVLINK_VERSION == 0)
#undef MAVLINK_VERSION
#define MAVLINK_VERSION 3
#endif

// MESSAGE DEFINITIONS
#include "./mavlink_msg_gimbal_manager_set_pitchyaw.h"
#include "./mavlink_msg_gimbal_manager_set_manual_control.h"
#include "./mavlink_msg_data16.h"
#include "./mavlink_msg_data32.h"
#include "./mavlink_msg_data64.h"
#include "./mavlink_msg_hy_request.h"
#include "./mavlink_msg_hy_version.h"
#include "./mavlink_msg_hy_gimbal_control.h"
#include "./mavlink_msg_hy_gimbal_calibration.h"
#include "./mavlink_msg_hy_gimbal_report.h"
#include "./mavlink_msg_hy_gimbal_channel_config.h"
#include "./mavlink_msg_hy_gimbal_data.h"
#include "./mavlink_msg_hy_laser_ranging.h"
#include "./mavlink_msg_hy_gimbal_camera.h"

// base include



#if MAVLINK_HY_GIMBAL_XML_HASH == MAVLINK_PRIMARY_XML_HASH
# define MAVLINK_MESSAGE_INFO {MAVLINK_MESSAGE_INFO_DATA16, MAVLINK_MESSAGE_INFO_DATA32, MAVLINK_MESSAGE_INFO_DATA64, MAVLINK_MESSAGE_INFO_GIMBAL_MANAGER_SET_PITCHYAW, MAVLINK_MESSAGE_INFO_GIMBAL_MANAGER_SET_MANUAL_CONTROL, MAVLINK_MESSAGE_INFO_HY_GIMBAL_DATA, MAVLINK_MESSAGE_INFO_HY_REQUEST, MAVLINK_MESSAGE_INFO_HY_VERSION, MAVLINK_MESSAGE_INFO_HY_GIMBAL_CONTROL, MAVLINK_MESSAGE_INFO_HY_GIMBAL_CALIBRATION, MAVLINK_MESSAGE_INFO_HY_GIMBAL_REPORT, MAVLINK_MESSAGE_INFO_HY_GIMBAL_CHANNEL_CONFIG, MAVLINK_MESSAGE_INFO_HY_LASER_RANGING, MAVLINK_MESSAGE_INFO_HY_GIMBAL_CAMERA}
# define MAVLINK_MESSAGE_NAMES {{ "DATA16", 169 }, { "DATA32", 170 }, { "DATA64", 171 }, { "GIMBAL_MANAGER_SET_MANUAL_CONTROL", 288 }, { "GIMBAL_MANAGER_SET_PITCHYAW", 287 }, { "HY_GIMBAL_CALIBRATION", 11051 }, { "HY_GIMBAL_CAMERA", 11060 }, { "HY_GIMBAL_CHANNEL_CONFIG", 11053 }, { "HY_GIMBAL_CONTROL", 11050 }, { "HY_GIMBAL_DATA", 5002 }, { "HY_GIMBAL_REPORT", 11052 }, { "HY_LASER_RANGING", 11054 }, { "HY_REQUEST", 11047 }, { "HY_VERSION", 11048 }}
# if MAVLINK_COMMAND_24BIT
#  include "../mavlink_get_info.h"
# endif
#endif

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MAVLINK_HY_GIMBAL_H
