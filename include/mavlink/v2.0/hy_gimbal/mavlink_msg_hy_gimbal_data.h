#pragma once
// MESSAGE HY_GIMBAL_DATA PACKING

#define MAVLINK_MSG_ID_HY_GIMBAL_DATA 5002


typedef struct __mavlink_hy_gimbal_data_t {
 uint8_t msg_type; /*<  gimbal debudata type.*/
 int8_t debug_data[49]; /*<  gimbal debudata.*/
} mavlink_hy_gimbal_data_t;

#define MAVLINK_MSG_ID_HY_GIMBAL_DATA_LEN 50
#define MAVLINK_MSG_ID_HY_GIMBAL_DATA_MIN_LEN 50
#define MAVLINK_MSG_ID_5002_LEN 50
#define MAVLINK_MSG_ID_5002_MIN_LEN 50

#define MAVLINK_MSG_ID_HY_GIMBAL_DATA_CRC 156
#define MAVLINK_MSG_ID_5002_CRC 156

#define MAVLINK_MSG_HY_GIMBAL_DATA_FIELD_DEBUG_DATA_LEN 49

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_HY_GIMBAL_DATA { \
    5002, \
    "HY_GIMBAL_DATA", \
    2, \
    {  { "msg_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_hy_gimbal_data_t, msg_type) }, \
         { "debug_data", NULL, MAVLINK_TYPE_INT8_T, 49, 1, offsetof(mavlink_hy_gimbal_data_t, debug_data) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_HY_GIMBAL_DATA { \
    "HY_GIMBAL_DATA", \
    2, \
    {  { "msg_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_hy_gimbal_data_t, msg_type) }, \
         { "debug_data", NULL, MAVLINK_TYPE_INT8_T, 49, 1, offsetof(mavlink_hy_gimbal_data_t, debug_data) }, \
         } \
}
#endif

/**
 * @brief Pack a hy_gimbal_data message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param msg_type  gimbal debudata type.
 * @param debug_data  gimbal debudata.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_hy_gimbal_data_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t msg_type, const int8_t *debug_data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HY_GIMBAL_DATA_LEN];
    _mav_put_uint8_t(buf, 0, msg_type);
    _mav_put_int8_t_array(buf, 1, debug_data, 49);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HY_GIMBAL_DATA_LEN);
#else
    mavlink_hy_gimbal_data_t packet;
    packet.msg_type = msg_type;
    mav_array_memcpy(packet.debug_data, debug_data, sizeof(int8_t)*49);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HY_GIMBAL_DATA_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_HY_GIMBAL_DATA;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_HY_GIMBAL_DATA_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_DATA_LEN, MAVLINK_MSG_ID_HY_GIMBAL_DATA_CRC);
}

/**
 * @brief Pack a hy_gimbal_data message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param msg_type  gimbal debudata type.
 * @param debug_data  gimbal debudata.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_hy_gimbal_data_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint8_t msg_type, const int8_t *debug_data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HY_GIMBAL_DATA_LEN];
    _mav_put_uint8_t(buf, 0, msg_type);
    _mav_put_int8_t_array(buf, 1, debug_data, 49);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HY_GIMBAL_DATA_LEN);
#else
    mavlink_hy_gimbal_data_t packet;
    packet.msg_type = msg_type;
    mav_array_memcpy(packet.debug_data, debug_data, sizeof(int8_t)*49);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HY_GIMBAL_DATA_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_HY_GIMBAL_DATA;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_HY_GIMBAL_DATA_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_DATA_LEN, MAVLINK_MSG_ID_HY_GIMBAL_DATA_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_HY_GIMBAL_DATA_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_DATA_LEN);
#endif
}

/**
 * @brief Pack a hy_gimbal_data message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param msg_type  gimbal debudata type.
 * @param debug_data  gimbal debudata.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_hy_gimbal_data_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t msg_type,const int8_t *debug_data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HY_GIMBAL_DATA_LEN];
    _mav_put_uint8_t(buf, 0, msg_type);
    _mav_put_int8_t_array(buf, 1, debug_data, 49);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HY_GIMBAL_DATA_LEN);
#else
    mavlink_hy_gimbal_data_t packet;
    packet.msg_type = msg_type;
    mav_array_memcpy(packet.debug_data, debug_data, sizeof(int8_t)*49);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HY_GIMBAL_DATA_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_HY_GIMBAL_DATA;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_HY_GIMBAL_DATA_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_DATA_LEN, MAVLINK_MSG_ID_HY_GIMBAL_DATA_CRC);
}

/**
 * @brief Encode a hy_gimbal_data struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param hy_gimbal_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_hy_gimbal_data_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_hy_gimbal_data_t* hy_gimbal_data)
{
    return mavlink_msg_hy_gimbal_data_pack(system_id, component_id, msg, hy_gimbal_data->msg_type, hy_gimbal_data->debug_data);
}

/**
 * @brief Encode a hy_gimbal_data struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param hy_gimbal_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_hy_gimbal_data_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_hy_gimbal_data_t* hy_gimbal_data)
{
    return mavlink_msg_hy_gimbal_data_pack_chan(system_id, component_id, chan, msg, hy_gimbal_data->msg_type, hy_gimbal_data->debug_data);
}

/**
 * @brief Encode a hy_gimbal_data struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param hy_gimbal_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_hy_gimbal_data_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_hy_gimbal_data_t* hy_gimbal_data)
{
    return mavlink_msg_hy_gimbal_data_pack_status(system_id, component_id, _status, msg,  hy_gimbal_data->msg_type, hy_gimbal_data->debug_data);
}

/**
 * @brief Send a hy_gimbal_data message
 * @param chan MAVLink channel to send the message
 *
 * @param msg_type  gimbal debudata type.
 * @param debug_data  gimbal debudata.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_hy_gimbal_data_send(mavlink_channel_t chan, uint8_t msg_type, const int8_t *debug_data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HY_GIMBAL_DATA_LEN];
    _mav_put_uint8_t(buf, 0, msg_type);
    _mav_put_int8_t_array(buf, 1, debug_data, 49);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_GIMBAL_DATA, buf, MAVLINK_MSG_ID_HY_GIMBAL_DATA_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_DATA_LEN, MAVLINK_MSG_ID_HY_GIMBAL_DATA_CRC);
#else
    mavlink_hy_gimbal_data_t packet;
    packet.msg_type = msg_type;
    mav_array_memcpy(packet.debug_data, debug_data, sizeof(int8_t)*49);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_GIMBAL_DATA, (const char *)&packet, MAVLINK_MSG_ID_HY_GIMBAL_DATA_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_DATA_LEN, MAVLINK_MSG_ID_HY_GIMBAL_DATA_CRC);
#endif
}

/**
 * @brief Send a hy_gimbal_data message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_hy_gimbal_data_send_struct(mavlink_channel_t chan, const mavlink_hy_gimbal_data_t* hy_gimbal_data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_hy_gimbal_data_send(chan, hy_gimbal_data->msg_type, hy_gimbal_data->debug_data);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_GIMBAL_DATA, (const char *)hy_gimbal_data, MAVLINK_MSG_ID_HY_GIMBAL_DATA_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_DATA_LEN, MAVLINK_MSG_ID_HY_GIMBAL_DATA_CRC);
#endif
}

#if MAVLINK_MSG_ID_HY_GIMBAL_DATA_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_hy_gimbal_data_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t msg_type, const int8_t *debug_data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, msg_type);
    _mav_put_int8_t_array(buf, 1, debug_data, 49);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_GIMBAL_DATA, buf, MAVLINK_MSG_ID_HY_GIMBAL_DATA_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_DATA_LEN, MAVLINK_MSG_ID_HY_GIMBAL_DATA_CRC);
#else
    mavlink_hy_gimbal_data_t *packet = (mavlink_hy_gimbal_data_t *)msgbuf;
    packet->msg_type = msg_type;
    mav_array_memcpy(packet->debug_data, debug_data, sizeof(int8_t)*49);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_GIMBAL_DATA, (const char *)packet, MAVLINK_MSG_ID_HY_GIMBAL_DATA_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_DATA_LEN, MAVLINK_MSG_ID_HY_GIMBAL_DATA_CRC);
#endif
}
#endif

#endif

// MESSAGE HY_GIMBAL_DATA UNPACKING


/**
 * @brief Get field msg_type from hy_gimbal_data message
 *
 * @return  gimbal debudata type.
 */
static inline uint8_t mavlink_msg_hy_gimbal_data_get_msg_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field debug_data from hy_gimbal_data message
 *
 * @return  gimbal debudata.
 */
static inline uint16_t mavlink_msg_hy_gimbal_data_get_debug_data(const mavlink_message_t* msg, int8_t *debug_data)
{
    return _MAV_RETURN_int8_t_array(msg, debug_data, 49,  1);
}

/**
 * @brief Decode a hy_gimbal_data message into a struct
 *
 * @param msg The message to decode
 * @param hy_gimbal_data C-struct to decode the message contents into
 */
static inline void mavlink_msg_hy_gimbal_data_decode(const mavlink_message_t* msg, mavlink_hy_gimbal_data_t* hy_gimbal_data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    hy_gimbal_data->msg_type = mavlink_msg_hy_gimbal_data_get_msg_type(msg);
    mavlink_msg_hy_gimbal_data_get_debug_data(msg, hy_gimbal_data->debug_data);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_HY_GIMBAL_DATA_LEN? msg->len : MAVLINK_MSG_ID_HY_GIMBAL_DATA_LEN;
        memset(hy_gimbal_data, 0, MAVLINK_MSG_ID_HY_GIMBAL_DATA_LEN);
    memcpy(hy_gimbal_data, _MAV_PAYLOAD(msg), len);
#endif
}
