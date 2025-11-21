#pragma once
// MESSAGE HY_LASER_RANGING PACKING

#define MAVLINK_MSG_ID_HY_LASER_RANGING 11054


typedef struct __mavlink_hy_laser_ranging_t {
 float distance; /*<  (unit m,).*/
} mavlink_hy_laser_ranging_t;

#define MAVLINK_MSG_ID_HY_LASER_RANGING_LEN 4
#define MAVLINK_MSG_ID_HY_LASER_RANGING_MIN_LEN 4
#define MAVLINK_MSG_ID_11054_LEN 4
#define MAVLINK_MSG_ID_11054_MIN_LEN 4

#define MAVLINK_MSG_ID_HY_LASER_RANGING_CRC 133
#define MAVLINK_MSG_ID_11054_CRC 133



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_HY_LASER_RANGING { \
    11054, \
    "HY_LASER_RANGING", \
    1, \
    {  { "distance", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_hy_laser_ranging_t, distance) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_HY_LASER_RANGING { \
    "HY_LASER_RANGING", \
    1, \
    {  { "distance", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_hy_laser_ranging_t, distance) }, \
         } \
}
#endif

/**
 * @brief Pack a hy_laser_ranging message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param distance  (unit m,).
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_hy_laser_ranging_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float distance)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HY_LASER_RANGING_LEN];
    _mav_put_float(buf, 0, distance);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HY_LASER_RANGING_LEN);
#else
    mavlink_hy_laser_ranging_t packet;
    packet.distance = distance;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HY_LASER_RANGING_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_HY_LASER_RANGING;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_HY_LASER_RANGING_MIN_LEN, MAVLINK_MSG_ID_HY_LASER_RANGING_LEN, MAVLINK_MSG_ID_HY_LASER_RANGING_CRC);
}

/**
 * @brief Pack a hy_laser_ranging message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param distance  (unit m,).
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_hy_laser_ranging_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               float distance)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HY_LASER_RANGING_LEN];
    _mav_put_float(buf, 0, distance);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HY_LASER_RANGING_LEN);
#else
    mavlink_hy_laser_ranging_t packet;
    packet.distance = distance;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HY_LASER_RANGING_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_HY_LASER_RANGING;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_HY_LASER_RANGING_MIN_LEN, MAVLINK_MSG_ID_HY_LASER_RANGING_LEN, MAVLINK_MSG_ID_HY_LASER_RANGING_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_HY_LASER_RANGING_MIN_LEN, MAVLINK_MSG_ID_HY_LASER_RANGING_LEN);
#endif
}

/**
 * @brief Pack a hy_laser_ranging message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param distance  (unit m,).
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_hy_laser_ranging_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float distance)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HY_LASER_RANGING_LEN];
    _mav_put_float(buf, 0, distance);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HY_LASER_RANGING_LEN);
#else
    mavlink_hy_laser_ranging_t packet;
    packet.distance = distance;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HY_LASER_RANGING_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_HY_LASER_RANGING;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_HY_LASER_RANGING_MIN_LEN, MAVLINK_MSG_ID_HY_LASER_RANGING_LEN, MAVLINK_MSG_ID_HY_LASER_RANGING_CRC);
}

/**
 * @brief Encode a hy_laser_ranging struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param hy_laser_ranging C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_hy_laser_ranging_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_hy_laser_ranging_t* hy_laser_ranging)
{
    return mavlink_msg_hy_laser_ranging_pack(system_id, component_id, msg, hy_laser_ranging->distance);
}

/**
 * @brief Encode a hy_laser_ranging struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param hy_laser_ranging C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_hy_laser_ranging_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_hy_laser_ranging_t* hy_laser_ranging)
{
    return mavlink_msg_hy_laser_ranging_pack_chan(system_id, component_id, chan, msg, hy_laser_ranging->distance);
}

/**
 * @brief Encode a hy_laser_ranging struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param hy_laser_ranging C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_hy_laser_ranging_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_hy_laser_ranging_t* hy_laser_ranging)
{
    return mavlink_msg_hy_laser_ranging_pack_status(system_id, component_id, _status, msg,  hy_laser_ranging->distance);
}

/**
 * @brief Send a hy_laser_ranging message
 * @param chan MAVLink channel to send the message
 *
 * @param distance  (unit m,).
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_hy_laser_ranging_send(mavlink_channel_t chan, float distance)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HY_LASER_RANGING_LEN];
    _mav_put_float(buf, 0, distance);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_LASER_RANGING, buf, MAVLINK_MSG_ID_HY_LASER_RANGING_MIN_LEN, MAVLINK_MSG_ID_HY_LASER_RANGING_LEN, MAVLINK_MSG_ID_HY_LASER_RANGING_CRC);
#else
    mavlink_hy_laser_ranging_t packet;
    packet.distance = distance;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_LASER_RANGING, (const char *)&packet, MAVLINK_MSG_ID_HY_LASER_RANGING_MIN_LEN, MAVLINK_MSG_ID_HY_LASER_RANGING_LEN, MAVLINK_MSG_ID_HY_LASER_RANGING_CRC);
#endif
}

/**
 * @brief Send a hy_laser_ranging message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_hy_laser_ranging_send_struct(mavlink_channel_t chan, const mavlink_hy_laser_ranging_t* hy_laser_ranging)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_hy_laser_ranging_send(chan, hy_laser_ranging->distance);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_LASER_RANGING, (const char *)hy_laser_ranging, MAVLINK_MSG_ID_HY_LASER_RANGING_MIN_LEN, MAVLINK_MSG_ID_HY_LASER_RANGING_LEN, MAVLINK_MSG_ID_HY_LASER_RANGING_CRC);
#endif
}

#if MAVLINK_MSG_ID_HY_LASER_RANGING_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_hy_laser_ranging_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float distance)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, distance);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_LASER_RANGING, buf, MAVLINK_MSG_ID_HY_LASER_RANGING_MIN_LEN, MAVLINK_MSG_ID_HY_LASER_RANGING_LEN, MAVLINK_MSG_ID_HY_LASER_RANGING_CRC);
#else
    mavlink_hy_laser_ranging_t *packet = (mavlink_hy_laser_ranging_t *)msgbuf;
    packet->distance = distance;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_LASER_RANGING, (const char *)packet, MAVLINK_MSG_ID_HY_LASER_RANGING_MIN_LEN, MAVLINK_MSG_ID_HY_LASER_RANGING_LEN, MAVLINK_MSG_ID_HY_LASER_RANGING_CRC);
#endif
}
#endif

#endif

// MESSAGE HY_LASER_RANGING UNPACKING


/**
 * @brief Get field distance from hy_laser_ranging message
 *
 * @return  (unit m,).
 */
static inline float mavlink_msg_hy_laser_ranging_get_distance(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Decode a hy_laser_ranging message into a struct
 *
 * @param msg The message to decode
 * @param hy_laser_ranging C-struct to decode the message contents into
 */
static inline void mavlink_msg_hy_laser_ranging_decode(const mavlink_message_t* msg, mavlink_hy_laser_ranging_t* hy_laser_ranging)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    hy_laser_ranging->distance = mavlink_msg_hy_laser_ranging_get_distance(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_HY_LASER_RANGING_LEN? msg->len : MAVLINK_MSG_ID_HY_LASER_RANGING_LEN;
        memset(hy_laser_ranging, 0, MAVLINK_MSG_ID_HY_LASER_RANGING_LEN);
    memcpy(hy_laser_ranging, _MAV_PAYLOAD(msg), len);
#endif
}
