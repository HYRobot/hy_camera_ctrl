#pragma once
// MESSAGE HY_GIMBAL_REPORT PACKING

#define MAVLINK_MSG_ID_HY_GIMBAL_REPORT 11052


typedef struct __mavlink_hy_gimbal_report_t {
 int16_t pitch_angle; /*<  Pitch angle(centi-degrees).*/
 int16_t roll_angle; /*<  Roll angle(centi-degrees).*/
 int16_t yaw_angle; /*<  Yaw  angle(centi-degrees).*/
 int16_t temperature; /*<  temperature * 10 feedback.*/
 uint8_t status; /*<  ( based enum MAV_STATUS_GIMBAL).*/
 uint8_t zoom_image_mode; /*<  0~5:zoom feedback,6~7 image mode.*/
} mavlink_hy_gimbal_report_t;

#define MAVLINK_MSG_ID_HY_GIMBAL_REPORT_LEN 10
#define MAVLINK_MSG_ID_HY_GIMBAL_REPORT_MIN_LEN 10
#define MAVLINK_MSG_ID_11052_LEN 10
#define MAVLINK_MSG_ID_11052_MIN_LEN 10

#define MAVLINK_MSG_ID_HY_GIMBAL_REPORT_CRC 130
#define MAVLINK_MSG_ID_11052_CRC 130



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_HY_GIMBAL_REPORT { \
    11052, \
    "HY_GIMBAL_REPORT", \
    6, \
    {  { "status", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_hy_gimbal_report_t, status) }, \
         { "pitch_angle", NULL, MAVLINK_TYPE_INT16_T, 0, 0, offsetof(mavlink_hy_gimbal_report_t, pitch_angle) }, \
         { "roll_angle", NULL, MAVLINK_TYPE_INT16_T, 0, 2, offsetof(mavlink_hy_gimbal_report_t, roll_angle) }, \
         { "yaw_angle", NULL, MAVLINK_TYPE_INT16_T, 0, 4, offsetof(mavlink_hy_gimbal_report_t, yaw_angle) }, \
         { "zoom_image_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 9, offsetof(mavlink_hy_gimbal_report_t, zoom_image_mode) }, \
         { "temperature", NULL, MAVLINK_TYPE_INT16_T, 0, 6, offsetof(mavlink_hy_gimbal_report_t, temperature) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_HY_GIMBAL_REPORT { \
    "HY_GIMBAL_REPORT", \
    6, \
    {  { "status", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_hy_gimbal_report_t, status) }, \
         { "pitch_angle", NULL, MAVLINK_TYPE_INT16_T, 0, 0, offsetof(mavlink_hy_gimbal_report_t, pitch_angle) }, \
         { "roll_angle", NULL, MAVLINK_TYPE_INT16_T, 0, 2, offsetof(mavlink_hy_gimbal_report_t, roll_angle) }, \
         { "yaw_angle", NULL, MAVLINK_TYPE_INT16_T, 0, 4, offsetof(mavlink_hy_gimbal_report_t, yaw_angle) }, \
         { "zoom_image_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 9, offsetof(mavlink_hy_gimbal_report_t, zoom_image_mode) }, \
         { "temperature", NULL, MAVLINK_TYPE_INT16_T, 0, 6, offsetof(mavlink_hy_gimbal_report_t, temperature) }, \
         } \
}
#endif

/**
 * @brief Pack a hy_gimbal_report message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param status  ( based enum MAV_STATUS_GIMBAL).
 * @param pitch_angle  Pitch angle(centi-degrees).
 * @param roll_angle  Roll angle(centi-degrees).
 * @param yaw_angle  Yaw  angle(centi-degrees).
 * @param zoom_image_mode  0~5:zoom feedback,6~7 image mode.
 * @param temperature  temperature * 10 feedback.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_hy_gimbal_report_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t status, int16_t pitch_angle, int16_t roll_angle, int16_t yaw_angle, uint8_t zoom_image_mode, int16_t temperature)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HY_GIMBAL_REPORT_LEN];
    _mav_put_int16_t(buf, 0, pitch_angle);
    _mav_put_int16_t(buf, 2, roll_angle);
    _mav_put_int16_t(buf, 4, yaw_angle);
    _mav_put_int16_t(buf, 6, temperature);
    _mav_put_uint8_t(buf, 8, status);
    _mav_put_uint8_t(buf, 9, zoom_image_mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HY_GIMBAL_REPORT_LEN);
#else
    mavlink_hy_gimbal_report_t packet;
    packet.pitch_angle = pitch_angle;
    packet.roll_angle = roll_angle;
    packet.yaw_angle = yaw_angle;
    packet.temperature = temperature;
    packet.status = status;
    packet.zoom_image_mode = zoom_image_mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HY_GIMBAL_REPORT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_HY_GIMBAL_REPORT;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_HY_GIMBAL_REPORT_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_REPORT_LEN, MAVLINK_MSG_ID_HY_GIMBAL_REPORT_CRC);
}

/**
 * @brief Pack a hy_gimbal_report message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param status  ( based enum MAV_STATUS_GIMBAL).
 * @param pitch_angle  Pitch angle(centi-degrees).
 * @param roll_angle  Roll angle(centi-degrees).
 * @param yaw_angle  Yaw  angle(centi-degrees).
 * @param zoom_image_mode  0~5:zoom feedback,6~7 image mode.
 * @param temperature  temperature * 10 feedback.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_hy_gimbal_report_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint8_t status, int16_t pitch_angle, int16_t roll_angle, int16_t yaw_angle, uint8_t zoom_image_mode, int16_t temperature)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HY_GIMBAL_REPORT_LEN];
    _mav_put_int16_t(buf, 0, pitch_angle);
    _mav_put_int16_t(buf, 2, roll_angle);
    _mav_put_int16_t(buf, 4, yaw_angle);
    _mav_put_int16_t(buf, 6, temperature);
    _mav_put_uint8_t(buf, 8, status);
    _mav_put_uint8_t(buf, 9, zoom_image_mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HY_GIMBAL_REPORT_LEN);
#else
    mavlink_hy_gimbal_report_t packet;
    packet.pitch_angle = pitch_angle;
    packet.roll_angle = roll_angle;
    packet.yaw_angle = yaw_angle;
    packet.temperature = temperature;
    packet.status = status;
    packet.zoom_image_mode = zoom_image_mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HY_GIMBAL_REPORT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_HY_GIMBAL_REPORT;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_HY_GIMBAL_REPORT_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_REPORT_LEN, MAVLINK_MSG_ID_HY_GIMBAL_REPORT_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_HY_GIMBAL_REPORT_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_REPORT_LEN);
#endif
}

/**
 * @brief Pack a hy_gimbal_report message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param status  ( based enum MAV_STATUS_GIMBAL).
 * @param pitch_angle  Pitch angle(centi-degrees).
 * @param roll_angle  Roll angle(centi-degrees).
 * @param yaw_angle  Yaw  angle(centi-degrees).
 * @param zoom_image_mode  0~5:zoom feedback,6~7 image mode.
 * @param temperature  temperature * 10 feedback.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_hy_gimbal_report_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t status,int16_t pitch_angle,int16_t roll_angle,int16_t yaw_angle,uint8_t zoom_image_mode,int16_t temperature)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HY_GIMBAL_REPORT_LEN];
    _mav_put_int16_t(buf, 0, pitch_angle);
    _mav_put_int16_t(buf, 2, roll_angle);
    _mav_put_int16_t(buf, 4, yaw_angle);
    _mav_put_int16_t(buf, 6, temperature);
    _mav_put_uint8_t(buf, 8, status);
    _mav_put_uint8_t(buf, 9, zoom_image_mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HY_GIMBAL_REPORT_LEN);
#else
    mavlink_hy_gimbal_report_t packet;
    packet.pitch_angle = pitch_angle;
    packet.roll_angle = roll_angle;
    packet.yaw_angle = yaw_angle;
    packet.temperature = temperature;
    packet.status = status;
    packet.zoom_image_mode = zoom_image_mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HY_GIMBAL_REPORT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_HY_GIMBAL_REPORT;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_HY_GIMBAL_REPORT_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_REPORT_LEN, MAVLINK_MSG_ID_HY_GIMBAL_REPORT_CRC);
}

/**
 * @brief Encode a hy_gimbal_report struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param hy_gimbal_report C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_hy_gimbal_report_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_hy_gimbal_report_t* hy_gimbal_report)
{
    return mavlink_msg_hy_gimbal_report_pack(system_id, component_id, msg, hy_gimbal_report->status, hy_gimbal_report->pitch_angle, hy_gimbal_report->roll_angle, hy_gimbal_report->yaw_angle, hy_gimbal_report->zoom_image_mode, hy_gimbal_report->temperature);
}

/**
 * @brief Encode a hy_gimbal_report struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param hy_gimbal_report C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_hy_gimbal_report_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_hy_gimbal_report_t* hy_gimbal_report)
{
    return mavlink_msg_hy_gimbal_report_pack_chan(system_id, component_id, chan, msg, hy_gimbal_report->status, hy_gimbal_report->pitch_angle, hy_gimbal_report->roll_angle, hy_gimbal_report->yaw_angle, hy_gimbal_report->zoom_image_mode, hy_gimbal_report->temperature);
}

/**
 * @brief Encode a hy_gimbal_report struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param hy_gimbal_report C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_hy_gimbal_report_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_hy_gimbal_report_t* hy_gimbal_report)
{
    return mavlink_msg_hy_gimbal_report_pack_status(system_id, component_id, _status, msg,  hy_gimbal_report->status, hy_gimbal_report->pitch_angle, hy_gimbal_report->roll_angle, hy_gimbal_report->yaw_angle, hy_gimbal_report->zoom_image_mode, hy_gimbal_report->temperature);
}

/**
 * @brief Send a hy_gimbal_report message
 * @param chan MAVLink channel to send the message
 *
 * @param status  ( based enum MAV_STATUS_GIMBAL).
 * @param pitch_angle  Pitch angle(centi-degrees).
 * @param roll_angle  Roll angle(centi-degrees).
 * @param yaw_angle  Yaw  angle(centi-degrees).
 * @param zoom_image_mode  0~5:zoom feedback,6~7 image mode.
 * @param temperature  temperature * 10 feedback.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_hy_gimbal_report_send(mavlink_channel_t chan, uint8_t status, int16_t pitch_angle, int16_t roll_angle, int16_t yaw_angle, uint8_t zoom_image_mode, int16_t temperature)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HY_GIMBAL_REPORT_LEN];
    _mav_put_int16_t(buf, 0, pitch_angle);
    _mav_put_int16_t(buf, 2, roll_angle);
    _mav_put_int16_t(buf, 4, yaw_angle);
    _mav_put_int16_t(buf, 6, temperature);
    _mav_put_uint8_t(buf, 8, status);
    _mav_put_uint8_t(buf, 9, zoom_image_mode);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_GIMBAL_REPORT, buf, MAVLINK_MSG_ID_HY_GIMBAL_REPORT_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_REPORT_LEN, MAVLINK_MSG_ID_HY_GIMBAL_REPORT_CRC);
#else
    mavlink_hy_gimbal_report_t packet;
    packet.pitch_angle = pitch_angle;
    packet.roll_angle = roll_angle;
    packet.yaw_angle = yaw_angle;
    packet.temperature = temperature;
    packet.status = status;
    packet.zoom_image_mode = zoom_image_mode;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_GIMBAL_REPORT, (const char *)&packet, MAVLINK_MSG_ID_HY_GIMBAL_REPORT_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_REPORT_LEN, MAVLINK_MSG_ID_HY_GIMBAL_REPORT_CRC);
#endif
}

/**
 * @brief Send a hy_gimbal_report message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_hy_gimbal_report_send_struct(mavlink_channel_t chan, const mavlink_hy_gimbal_report_t* hy_gimbal_report)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_hy_gimbal_report_send(chan, hy_gimbal_report->status, hy_gimbal_report->pitch_angle, hy_gimbal_report->roll_angle, hy_gimbal_report->yaw_angle, hy_gimbal_report->zoom_image_mode, hy_gimbal_report->temperature);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_GIMBAL_REPORT, (const char *)hy_gimbal_report, MAVLINK_MSG_ID_HY_GIMBAL_REPORT_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_REPORT_LEN, MAVLINK_MSG_ID_HY_GIMBAL_REPORT_CRC);
#endif
}

#if MAVLINK_MSG_ID_HY_GIMBAL_REPORT_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_hy_gimbal_report_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t status, int16_t pitch_angle, int16_t roll_angle, int16_t yaw_angle, uint8_t zoom_image_mode, int16_t temperature)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int16_t(buf, 0, pitch_angle);
    _mav_put_int16_t(buf, 2, roll_angle);
    _mav_put_int16_t(buf, 4, yaw_angle);
    _mav_put_int16_t(buf, 6, temperature);
    _mav_put_uint8_t(buf, 8, status);
    _mav_put_uint8_t(buf, 9, zoom_image_mode);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_GIMBAL_REPORT, buf, MAVLINK_MSG_ID_HY_GIMBAL_REPORT_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_REPORT_LEN, MAVLINK_MSG_ID_HY_GIMBAL_REPORT_CRC);
#else
    mavlink_hy_gimbal_report_t *packet = (mavlink_hy_gimbal_report_t *)msgbuf;
    packet->pitch_angle = pitch_angle;
    packet->roll_angle = roll_angle;
    packet->yaw_angle = yaw_angle;
    packet->temperature = temperature;
    packet->status = status;
    packet->zoom_image_mode = zoom_image_mode;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_GIMBAL_REPORT, (const char *)packet, MAVLINK_MSG_ID_HY_GIMBAL_REPORT_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_REPORT_LEN, MAVLINK_MSG_ID_HY_GIMBAL_REPORT_CRC);
#endif
}
#endif

#endif

// MESSAGE HY_GIMBAL_REPORT UNPACKING


/**
 * @brief Get field status from hy_gimbal_report message
 *
 * @return  ( based enum MAV_STATUS_GIMBAL).
 */
static inline uint8_t mavlink_msg_hy_gimbal_report_get_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  8);
}

/**
 * @brief Get field pitch_angle from hy_gimbal_report message
 *
 * @return  Pitch angle(centi-degrees).
 */
static inline int16_t mavlink_msg_hy_gimbal_report_get_pitch_angle(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  0);
}

/**
 * @brief Get field roll_angle from hy_gimbal_report message
 *
 * @return  Roll angle(centi-degrees).
 */
static inline int16_t mavlink_msg_hy_gimbal_report_get_roll_angle(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  2);
}

/**
 * @brief Get field yaw_angle from hy_gimbal_report message
 *
 * @return  Yaw  angle(centi-degrees).
 */
static inline int16_t mavlink_msg_hy_gimbal_report_get_yaw_angle(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  4);
}

/**
 * @brief Get field zoom_image_mode from hy_gimbal_report message
 *
 * @return  0~5:zoom feedback,6~7 image mode.
 */
static inline uint8_t mavlink_msg_hy_gimbal_report_get_zoom_image_mode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  9);
}

/**
 * @brief Get field temperature from hy_gimbal_report message
 *
 * @return  temperature * 10 feedback.
 */
static inline int16_t mavlink_msg_hy_gimbal_report_get_temperature(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  6);
}

/**
 * @brief Decode a hy_gimbal_report message into a struct
 *
 * @param msg The message to decode
 * @param hy_gimbal_report C-struct to decode the message contents into
 */
static inline void mavlink_msg_hy_gimbal_report_decode(const mavlink_message_t* msg, mavlink_hy_gimbal_report_t* hy_gimbal_report)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    hy_gimbal_report->pitch_angle = mavlink_msg_hy_gimbal_report_get_pitch_angle(msg);
    hy_gimbal_report->roll_angle = mavlink_msg_hy_gimbal_report_get_roll_angle(msg);
    hy_gimbal_report->yaw_angle = mavlink_msg_hy_gimbal_report_get_yaw_angle(msg);
    hy_gimbal_report->temperature = mavlink_msg_hy_gimbal_report_get_temperature(msg);
    hy_gimbal_report->status = mavlink_msg_hy_gimbal_report_get_status(msg);
    hy_gimbal_report->zoom_image_mode = mavlink_msg_hy_gimbal_report_get_zoom_image_mode(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_HY_GIMBAL_REPORT_LEN? msg->len : MAVLINK_MSG_ID_HY_GIMBAL_REPORT_LEN;
        memset(hy_gimbal_report, 0, MAVLINK_MSG_ID_HY_GIMBAL_REPORT_LEN);
    memcpy(hy_gimbal_report, _MAV_PAYLOAD(msg), len);
#endif
}
