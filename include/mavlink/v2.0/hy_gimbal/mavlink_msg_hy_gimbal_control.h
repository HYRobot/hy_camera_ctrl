#pragma once
// MESSAGE HY_GIMBAL_CONTROL PACKING

#define MAVLINK_MSG_ID_HY_GIMBAL_CONTROL 11050


typedef struct __mavlink_hy_gimbal_control_t {
 int16_t pitch_angle; /*<  Pitch target angle(centi-degrees).*/
 int16_t yaw_angle; /*<  Yaw target angle(centi-degrees).*/
 int16_t pitch_rate; /*< [degree/s] Demanded  pitch rate.*/
 int16_t yaw_rate; /*< [degree/s] Demanded  yaw rate.*/
 uint8_t stab_pitch; /*<  (2 = angle, 1 = rate).*/
 uint8_t stab_yaw; /*<  (3:yaw global head,2 = yaw follow head, 1 = rate).*/
} mavlink_hy_gimbal_control_t;

#define MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_LEN 10
#define MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_MIN_LEN 10
#define MAVLINK_MSG_ID_11050_LEN 10
#define MAVLINK_MSG_ID_11050_MIN_LEN 10

#define MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_CRC 217
#define MAVLINK_MSG_ID_11050_CRC 217



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_HY_GIMBAL_CONTROL { \
    11050, \
    "HY_GIMBAL_CONTROL", \
    6, \
    {  { "stab_pitch", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_hy_gimbal_control_t, stab_pitch) }, \
         { "stab_yaw", NULL, MAVLINK_TYPE_UINT8_T, 0, 9, offsetof(mavlink_hy_gimbal_control_t, stab_yaw) }, \
         { "pitch_angle", NULL, MAVLINK_TYPE_INT16_T, 0, 0, offsetof(mavlink_hy_gimbal_control_t, pitch_angle) }, \
         { "yaw_angle", NULL, MAVLINK_TYPE_INT16_T, 0, 2, offsetof(mavlink_hy_gimbal_control_t, yaw_angle) }, \
         { "pitch_rate", NULL, MAVLINK_TYPE_INT16_T, 0, 4, offsetof(mavlink_hy_gimbal_control_t, pitch_rate) }, \
         { "yaw_rate", NULL, MAVLINK_TYPE_INT16_T, 0, 6, offsetof(mavlink_hy_gimbal_control_t, yaw_rate) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_HY_GIMBAL_CONTROL { \
    "HY_GIMBAL_CONTROL", \
    6, \
    {  { "stab_pitch", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_hy_gimbal_control_t, stab_pitch) }, \
         { "stab_yaw", NULL, MAVLINK_TYPE_UINT8_T, 0, 9, offsetof(mavlink_hy_gimbal_control_t, stab_yaw) }, \
         { "pitch_angle", NULL, MAVLINK_TYPE_INT16_T, 0, 0, offsetof(mavlink_hy_gimbal_control_t, pitch_angle) }, \
         { "yaw_angle", NULL, MAVLINK_TYPE_INT16_T, 0, 2, offsetof(mavlink_hy_gimbal_control_t, yaw_angle) }, \
         { "pitch_rate", NULL, MAVLINK_TYPE_INT16_T, 0, 4, offsetof(mavlink_hy_gimbal_control_t, pitch_rate) }, \
         { "yaw_rate", NULL, MAVLINK_TYPE_INT16_T, 0, 6, offsetof(mavlink_hy_gimbal_control_t, yaw_rate) }, \
         } \
}
#endif

/**
 * @brief Pack a hy_gimbal_control message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param stab_pitch  (2 = angle, 1 = rate).
 * @param stab_yaw  (3:yaw global head,2 = yaw follow head, 1 = rate).
 * @param pitch_angle  Pitch target angle(centi-degrees).
 * @param yaw_angle  Yaw target angle(centi-degrees).
 * @param pitch_rate [degree/s] Demanded  pitch rate.
 * @param yaw_rate [degree/s] Demanded  yaw rate.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_hy_gimbal_control_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t stab_pitch, uint8_t stab_yaw, int16_t pitch_angle, int16_t yaw_angle, int16_t pitch_rate, int16_t yaw_rate)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_LEN];
    _mav_put_int16_t(buf, 0, pitch_angle);
    _mav_put_int16_t(buf, 2, yaw_angle);
    _mav_put_int16_t(buf, 4, pitch_rate);
    _mav_put_int16_t(buf, 6, yaw_rate);
    _mav_put_uint8_t(buf, 8, stab_pitch);
    _mav_put_uint8_t(buf, 9, stab_yaw);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_LEN);
#else
    mavlink_hy_gimbal_control_t packet;
    packet.pitch_angle = pitch_angle;
    packet.yaw_angle = yaw_angle;
    packet.pitch_rate = pitch_rate;
    packet.yaw_rate = yaw_rate;
    packet.stab_pitch = stab_pitch;
    packet.stab_yaw = stab_yaw;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_HY_GIMBAL_CONTROL;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_CRC);
}

/**
 * @brief Pack a hy_gimbal_control message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param stab_pitch  (2 = angle, 1 = rate).
 * @param stab_yaw  (3:yaw global head,2 = yaw follow head, 1 = rate).
 * @param pitch_angle  Pitch target angle(centi-degrees).
 * @param yaw_angle  Yaw target angle(centi-degrees).
 * @param pitch_rate [degree/s] Demanded  pitch rate.
 * @param yaw_rate [degree/s] Demanded  yaw rate.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_hy_gimbal_control_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint8_t stab_pitch, uint8_t stab_yaw, int16_t pitch_angle, int16_t yaw_angle, int16_t pitch_rate, int16_t yaw_rate)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_LEN];
    _mav_put_int16_t(buf, 0, pitch_angle);
    _mav_put_int16_t(buf, 2, yaw_angle);
    _mav_put_int16_t(buf, 4, pitch_rate);
    _mav_put_int16_t(buf, 6, yaw_rate);
    _mav_put_uint8_t(buf, 8, stab_pitch);
    _mav_put_uint8_t(buf, 9, stab_yaw);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_LEN);
#else
    mavlink_hy_gimbal_control_t packet;
    packet.pitch_angle = pitch_angle;
    packet.yaw_angle = yaw_angle;
    packet.pitch_rate = pitch_rate;
    packet.yaw_rate = yaw_rate;
    packet.stab_pitch = stab_pitch;
    packet.stab_yaw = stab_yaw;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_HY_GIMBAL_CONTROL;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_LEN);
#endif
}

/**
 * @brief Pack a hy_gimbal_control message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param stab_pitch  (2 = angle, 1 = rate).
 * @param stab_yaw  (3:yaw global head,2 = yaw follow head, 1 = rate).
 * @param pitch_angle  Pitch target angle(centi-degrees).
 * @param yaw_angle  Yaw target angle(centi-degrees).
 * @param pitch_rate [degree/s] Demanded  pitch rate.
 * @param yaw_rate [degree/s] Demanded  yaw rate.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_hy_gimbal_control_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t stab_pitch,uint8_t stab_yaw,int16_t pitch_angle,int16_t yaw_angle,int16_t pitch_rate,int16_t yaw_rate)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_LEN];
    _mav_put_int16_t(buf, 0, pitch_angle);
    _mav_put_int16_t(buf, 2, yaw_angle);
    _mav_put_int16_t(buf, 4, pitch_rate);
    _mav_put_int16_t(buf, 6, yaw_rate);
    _mav_put_uint8_t(buf, 8, stab_pitch);
    _mav_put_uint8_t(buf, 9, stab_yaw);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_LEN);
#else
    mavlink_hy_gimbal_control_t packet;
    packet.pitch_angle = pitch_angle;
    packet.yaw_angle = yaw_angle;
    packet.pitch_rate = pitch_rate;
    packet.yaw_rate = yaw_rate;
    packet.stab_pitch = stab_pitch;
    packet.stab_yaw = stab_yaw;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_HY_GIMBAL_CONTROL;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_CRC);
}

/**
 * @brief Encode a hy_gimbal_control struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param hy_gimbal_control C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_hy_gimbal_control_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_hy_gimbal_control_t* hy_gimbal_control)
{
    return mavlink_msg_hy_gimbal_control_pack(system_id, component_id, msg, hy_gimbal_control->stab_pitch, hy_gimbal_control->stab_yaw, hy_gimbal_control->pitch_angle, hy_gimbal_control->yaw_angle, hy_gimbal_control->pitch_rate, hy_gimbal_control->yaw_rate);
}

/**
 * @brief Encode a hy_gimbal_control struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param hy_gimbal_control C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_hy_gimbal_control_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_hy_gimbal_control_t* hy_gimbal_control)
{
    return mavlink_msg_hy_gimbal_control_pack_chan(system_id, component_id, chan, msg, hy_gimbal_control->stab_pitch, hy_gimbal_control->stab_yaw, hy_gimbal_control->pitch_angle, hy_gimbal_control->yaw_angle, hy_gimbal_control->pitch_rate, hy_gimbal_control->yaw_rate);
}

/**
 * @brief Encode a hy_gimbal_control struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param hy_gimbal_control C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_hy_gimbal_control_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_hy_gimbal_control_t* hy_gimbal_control)
{
    return mavlink_msg_hy_gimbal_control_pack_status(system_id, component_id, _status, msg,  hy_gimbal_control->stab_pitch, hy_gimbal_control->stab_yaw, hy_gimbal_control->pitch_angle, hy_gimbal_control->yaw_angle, hy_gimbal_control->pitch_rate, hy_gimbal_control->yaw_rate);
}

/**
 * @brief Send a hy_gimbal_control message
 * @param chan MAVLink channel to send the message
 *
 * @param stab_pitch  (2 = angle, 1 = rate).
 * @param stab_yaw  (3:yaw global head,2 = yaw follow head, 1 = rate).
 * @param pitch_angle  Pitch target angle(centi-degrees).
 * @param yaw_angle  Yaw target angle(centi-degrees).
 * @param pitch_rate [degree/s] Demanded  pitch rate.
 * @param yaw_rate [degree/s] Demanded  yaw rate.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_hy_gimbal_control_send(mavlink_channel_t chan, uint8_t stab_pitch, uint8_t stab_yaw, int16_t pitch_angle, int16_t yaw_angle, int16_t pitch_rate, int16_t yaw_rate)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_LEN];
    _mav_put_int16_t(buf, 0, pitch_angle);
    _mav_put_int16_t(buf, 2, yaw_angle);
    _mav_put_int16_t(buf, 4, pitch_rate);
    _mav_put_int16_t(buf, 6, yaw_rate);
    _mav_put_uint8_t(buf, 8, stab_pitch);
    _mav_put_uint8_t(buf, 9, stab_yaw);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL, buf, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_CRC);
#else
    mavlink_hy_gimbal_control_t packet;
    packet.pitch_angle = pitch_angle;
    packet.yaw_angle = yaw_angle;
    packet.pitch_rate = pitch_rate;
    packet.yaw_rate = yaw_rate;
    packet.stab_pitch = stab_pitch;
    packet.stab_yaw = stab_yaw;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL, (const char *)&packet, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_CRC);
#endif
}

/**
 * @brief Send a hy_gimbal_control message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_hy_gimbal_control_send_struct(mavlink_channel_t chan, const mavlink_hy_gimbal_control_t* hy_gimbal_control)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_hy_gimbal_control_send(chan, hy_gimbal_control->stab_pitch, hy_gimbal_control->stab_yaw, hy_gimbal_control->pitch_angle, hy_gimbal_control->yaw_angle, hy_gimbal_control->pitch_rate, hy_gimbal_control->yaw_rate);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL, (const char *)hy_gimbal_control, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_CRC);
#endif
}

#if MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_hy_gimbal_control_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t stab_pitch, uint8_t stab_yaw, int16_t pitch_angle, int16_t yaw_angle, int16_t pitch_rate, int16_t yaw_rate)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int16_t(buf, 0, pitch_angle);
    _mav_put_int16_t(buf, 2, yaw_angle);
    _mav_put_int16_t(buf, 4, pitch_rate);
    _mav_put_int16_t(buf, 6, yaw_rate);
    _mav_put_uint8_t(buf, 8, stab_pitch);
    _mav_put_uint8_t(buf, 9, stab_yaw);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL, buf, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_CRC);
#else
    mavlink_hy_gimbal_control_t *packet = (mavlink_hy_gimbal_control_t *)msgbuf;
    packet->pitch_angle = pitch_angle;
    packet->yaw_angle = yaw_angle;
    packet->pitch_rate = pitch_rate;
    packet->yaw_rate = yaw_rate;
    packet->stab_pitch = stab_pitch;
    packet->stab_yaw = stab_yaw;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL, (const char *)packet, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_CRC);
#endif
}
#endif

#endif

// MESSAGE HY_GIMBAL_CONTROL UNPACKING


/**
 * @brief Get field stab_pitch from hy_gimbal_control message
 *
 * @return  (2 = angle, 1 = rate).
 */
static inline uint8_t mavlink_msg_hy_gimbal_control_get_stab_pitch(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  8);
}

/**
 * @brief Get field stab_yaw from hy_gimbal_control message
 *
 * @return  (3:yaw global head,2 = yaw follow head, 1 = rate).
 */
static inline uint8_t mavlink_msg_hy_gimbal_control_get_stab_yaw(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  9);
}

/**
 * @brief Get field pitch_angle from hy_gimbal_control message
 *
 * @return  Pitch target angle(centi-degrees).
 */
static inline int16_t mavlink_msg_hy_gimbal_control_get_pitch_angle(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  0);
}

/**
 * @brief Get field yaw_angle from hy_gimbal_control message
 *
 * @return  Yaw target angle(centi-degrees).
 */
static inline int16_t mavlink_msg_hy_gimbal_control_get_yaw_angle(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  2);
}

/**
 * @brief Get field pitch_rate from hy_gimbal_control message
 *
 * @return [degree/s] Demanded  pitch rate.
 */
static inline int16_t mavlink_msg_hy_gimbal_control_get_pitch_rate(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  4);
}

/**
 * @brief Get field yaw_rate from hy_gimbal_control message
 *
 * @return [degree/s] Demanded  yaw rate.
 */
static inline int16_t mavlink_msg_hy_gimbal_control_get_yaw_rate(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  6);
}

/**
 * @brief Decode a hy_gimbal_control message into a struct
 *
 * @param msg The message to decode
 * @param hy_gimbal_control C-struct to decode the message contents into
 */
static inline void mavlink_msg_hy_gimbal_control_decode(const mavlink_message_t* msg, mavlink_hy_gimbal_control_t* hy_gimbal_control)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    hy_gimbal_control->pitch_angle = mavlink_msg_hy_gimbal_control_get_pitch_angle(msg);
    hy_gimbal_control->yaw_angle = mavlink_msg_hy_gimbal_control_get_yaw_angle(msg);
    hy_gimbal_control->pitch_rate = mavlink_msg_hy_gimbal_control_get_pitch_rate(msg);
    hy_gimbal_control->yaw_rate = mavlink_msg_hy_gimbal_control_get_yaw_rate(msg);
    hy_gimbal_control->stab_pitch = mavlink_msg_hy_gimbal_control_get_stab_pitch(msg);
    hy_gimbal_control->stab_yaw = mavlink_msg_hy_gimbal_control_get_stab_yaw(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_LEN? msg->len : MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_LEN;
        memset(hy_gimbal_control, 0, MAVLINK_MSG_ID_HY_GIMBAL_CONTROL_LEN);
    memcpy(hy_gimbal_control, _MAV_PAYLOAD(msg), len);
#endif
}
