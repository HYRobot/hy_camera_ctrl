#pragma once
// MESSAGE HY_VERSION PACKING

#define MAVLINK_MSG_ID_HY_VERSION 11048


typedef struct __mavlink_hy_version_t {
 uint8_t gimbal_communi_version; /*<  (version*10).*/
 uint8_t gimbal_mainboard_version; /*<  (version*10).*/
} mavlink_hy_version_t;

#define MAVLINK_MSG_ID_HY_VERSION_LEN 2
#define MAVLINK_MSG_ID_HY_VERSION_MIN_LEN 2
#define MAVLINK_MSG_ID_11048_LEN 2
#define MAVLINK_MSG_ID_11048_MIN_LEN 2

#define MAVLINK_MSG_ID_HY_VERSION_CRC 196
#define MAVLINK_MSG_ID_11048_CRC 196



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_HY_VERSION { \
    11048, \
    "HY_VERSION", \
    2, \
    {  { "gimbal_communi_version", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_hy_version_t, gimbal_communi_version) }, \
         { "gimbal_mainboard_version", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_hy_version_t, gimbal_mainboard_version) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_HY_VERSION { \
    "HY_VERSION", \
    2, \
    {  { "gimbal_communi_version", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_hy_version_t, gimbal_communi_version) }, \
         { "gimbal_mainboard_version", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_hy_version_t, gimbal_mainboard_version) }, \
         } \
}
#endif

/**
 * @brief Pack a hy_version message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param gimbal_communi_version  (version*10).
 * @param gimbal_mainboard_version  (version*10).
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_hy_version_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t gimbal_communi_version, uint8_t gimbal_mainboard_version)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HY_VERSION_LEN];
    _mav_put_uint8_t(buf, 0, gimbal_communi_version);
    _mav_put_uint8_t(buf, 1, gimbal_mainboard_version);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HY_VERSION_LEN);
#else
    mavlink_hy_version_t packet;
    packet.gimbal_communi_version = gimbal_communi_version;
    packet.gimbal_mainboard_version = gimbal_mainboard_version;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HY_VERSION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_HY_VERSION;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_HY_VERSION_MIN_LEN, MAVLINK_MSG_ID_HY_VERSION_LEN, MAVLINK_MSG_ID_HY_VERSION_CRC);
}

/**
 * @brief Pack a hy_version message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param gimbal_communi_version  (version*10).
 * @param gimbal_mainboard_version  (version*10).
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_hy_version_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint8_t gimbal_communi_version, uint8_t gimbal_mainboard_version)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HY_VERSION_LEN];
    _mav_put_uint8_t(buf, 0, gimbal_communi_version);
    _mav_put_uint8_t(buf, 1, gimbal_mainboard_version);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HY_VERSION_LEN);
#else
    mavlink_hy_version_t packet;
    packet.gimbal_communi_version = gimbal_communi_version;
    packet.gimbal_mainboard_version = gimbal_mainboard_version;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HY_VERSION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_HY_VERSION;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_HY_VERSION_MIN_LEN, MAVLINK_MSG_ID_HY_VERSION_LEN, MAVLINK_MSG_ID_HY_VERSION_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_HY_VERSION_MIN_LEN, MAVLINK_MSG_ID_HY_VERSION_LEN);
#endif
}

/**
 * @brief Pack a hy_version message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param gimbal_communi_version  (version*10).
 * @param gimbal_mainboard_version  (version*10).
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_hy_version_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t gimbal_communi_version,uint8_t gimbal_mainboard_version)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HY_VERSION_LEN];
    _mav_put_uint8_t(buf, 0, gimbal_communi_version);
    _mav_put_uint8_t(buf, 1, gimbal_mainboard_version);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HY_VERSION_LEN);
#else
    mavlink_hy_version_t packet;
    packet.gimbal_communi_version = gimbal_communi_version;
    packet.gimbal_mainboard_version = gimbal_mainboard_version;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HY_VERSION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_HY_VERSION;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_HY_VERSION_MIN_LEN, MAVLINK_MSG_ID_HY_VERSION_LEN, MAVLINK_MSG_ID_HY_VERSION_CRC);
}

/**
 * @brief Encode a hy_version struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param hy_version C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_hy_version_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_hy_version_t* hy_version)
{
    return mavlink_msg_hy_version_pack(system_id, component_id, msg, hy_version->gimbal_communi_version, hy_version->gimbal_mainboard_version);
}

/**
 * @brief Encode a hy_version struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param hy_version C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_hy_version_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_hy_version_t* hy_version)
{
    return mavlink_msg_hy_version_pack_chan(system_id, component_id, chan, msg, hy_version->gimbal_communi_version, hy_version->gimbal_mainboard_version);
}

/**
 * @brief Encode a hy_version struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param hy_version C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_hy_version_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_hy_version_t* hy_version)
{
    return mavlink_msg_hy_version_pack_status(system_id, component_id, _status, msg,  hy_version->gimbal_communi_version, hy_version->gimbal_mainboard_version);
}

/**
 * @brief Send a hy_version message
 * @param chan MAVLink channel to send the message
 *
 * @param gimbal_communi_version  (version*10).
 * @param gimbal_mainboard_version  (version*10).
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_hy_version_send(mavlink_channel_t chan, uint8_t gimbal_communi_version, uint8_t gimbal_mainboard_version)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HY_VERSION_LEN];
    _mav_put_uint8_t(buf, 0, gimbal_communi_version);
    _mav_put_uint8_t(buf, 1, gimbal_mainboard_version);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_VERSION, buf, MAVLINK_MSG_ID_HY_VERSION_MIN_LEN, MAVLINK_MSG_ID_HY_VERSION_LEN, MAVLINK_MSG_ID_HY_VERSION_CRC);
#else
    mavlink_hy_version_t packet;
    packet.gimbal_communi_version = gimbal_communi_version;
    packet.gimbal_mainboard_version = gimbal_mainboard_version;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_VERSION, (const char *)&packet, MAVLINK_MSG_ID_HY_VERSION_MIN_LEN, MAVLINK_MSG_ID_HY_VERSION_LEN, MAVLINK_MSG_ID_HY_VERSION_CRC);
#endif
}

/**
 * @brief Send a hy_version message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_hy_version_send_struct(mavlink_channel_t chan, const mavlink_hy_version_t* hy_version)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_hy_version_send(chan, hy_version->gimbal_communi_version, hy_version->gimbal_mainboard_version);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_VERSION, (const char *)hy_version, MAVLINK_MSG_ID_HY_VERSION_MIN_LEN, MAVLINK_MSG_ID_HY_VERSION_LEN, MAVLINK_MSG_ID_HY_VERSION_CRC);
#endif
}

#if MAVLINK_MSG_ID_HY_VERSION_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_hy_version_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t gimbal_communi_version, uint8_t gimbal_mainboard_version)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, gimbal_communi_version);
    _mav_put_uint8_t(buf, 1, gimbal_mainboard_version);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_VERSION, buf, MAVLINK_MSG_ID_HY_VERSION_MIN_LEN, MAVLINK_MSG_ID_HY_VERSION_LEN, MAVLINK_MSG_ID_HY_VERSION_CRC);
#else
    mavlink_hy_version_t *packet = (mavlink_hy_version_t *)msgbuf;
    packet->gimbal_communi_version = gimbal_communi_version;
    packet->gimbal_mainboard_version = gimbal_mainboard_version;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_VERSION, (const char *)packet, MAVLINK_MSG_ID_HY_VERSION_MIN_LEN, MAVLINK_MSG_ID_HY_VERSION_LEN, MAVLINK_MSG_ID_HY_VERSION_CRC);
#endif
}
#endif

#endif

// MESSAGE HY_VERSION UNPACKING


/**
 * @brief Get field gimbal_communi_version from hy_version message
 *
 * @return  (version*10).
 */
static inline uint8_t mavlink_msg_hy_version_get_gimbal_communi_version(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field gimbal_mainboard_version from hy_version message
 *
 * @return  (version*10).
 */
static inline uint8_t mavlink_msg_hy_version_get_gimbal_mainboard_version(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Decode a hy_version message into a struct
 *
 * @param msg The message to decode
 * @param hy_version C-struct to decode the message contents into
 */
static inline void mavlink_msg_hy_version_decode(const mavlink_message_t* msg, mavlink_hy_version_t* hy_version)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    hy_version->gimbal_communi_version = mavlink_msg_hy_version_get_gimbal_communi_version(msg);
    hy_version->gimbal_mainboard_version = mavlink_msg_hy_version_get_gimbal_mainboard_version(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_HY_VERSION_LEN? msg->len : MAVLINK_MSG_ID_HY_VERSION_LEN;
        memset(hy_version, 0, MAVLINK_MSG_ID_HY_VERSION_LEN);
    memcpy(hy_version, _MAV_PAYLOAD(msg), len);
#endif
}
