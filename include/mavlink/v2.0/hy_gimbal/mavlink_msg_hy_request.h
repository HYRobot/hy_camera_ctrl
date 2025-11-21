#pragma once
// MESSAGE HY_REQUEST PACKING

#define MAVLINK_MSG_ID_HY_REQUEST 11047


typedef struct __mavlink_hy_request_t {
 uint8_t request; /*<  (based on REQUEST_CMD_TYPES).*/
} mavlink_hy_request_t;

#define MAVLINK_MSG_ID_HY_REQUEST_LEN 1
#define MAVLINK_MSG_ID_HY_REQUEST_MIN_LEN 1
#define MAVLINK_MSG_ID_11047_LEN 1
#define MAVLINK_MSG_ID_11047_MIN_LEN 1

#define MAVLINK_MSG_ID_HY_REQUEST_CRC 74
#define MAVLINK_MSG_ID_11047_CRC 74



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_HY_REQUEST { \
    11047, \
    "HY_REQUEST", \
    1, \
    {  { "request", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_hy_request_t, request) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_HY_REQUEST { \
    "HY_REQUEST", \
    1, \
    {  { "request", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_hy_request_t, request) }, \
         } \
}
#endif

/**
 * @brief Pack a hy_request message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param request  (based on REQUEST_CMD_TYPES).
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_hy_request_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t request)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HY_REQUEST_LEN];
    _mav_put_uint8_t(buf, 0, request);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HY_REQUEST_LEN);
#else
    mavlink_hy_request_t packet;
    packet.request = request;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HY_REQUEST_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_HY_REQUEST;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_HY_REQUEST_MIN_LEN, MAVLINK_MSG_ID_HY_REQUEST_LEN, MAVLINK_MSG_ID_HY_REQUEST_CRC);
}

/**
 * @brief Pack a hy_request message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param request  (based on REQUEST_CMD_TYPES).
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_hy_request_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint8_t request)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HY_REQUEST_LEN];
    _mav_put_uint8_t(buf, 0, request);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HY_REQUEST_LEN);
#else
    mavlink_hy_request_t packet;
    packet.request = request;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HY_REQUEST_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_HY_REQUEST;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_HY_REQUEST_MIN_LEN, MAVLINK_MSG_ID_HY_REQUEST_LEN, MAVLINK_MSG_ID_HY_REQUEST_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_HY_REQUEST_MIN_LEN, MAVLINK_MSG_ID_HY_REQUEST_LEN);
#endif
}

/**
 * @brief Pack a hy_request message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param request  (based on REQUEST_CMD_TYPES).
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_hy_request_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t request)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HY_REQUEST_LEN];
    _mav_put_uint8_t(buf, 0, request);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HY_REQUEST_LEN);
#else
    mavlink_hy_request_t packet;
    packet.request = request;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HY_REQUEST_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_HY_REQUEST;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_HY_REQUEST_MIN_LEN, MAVLINK_MSG_ID_HY_REQUEST_LEN, MAVLINK_MSG_ID_HY_REQUEST_CRC);
}

/**
 * @brief Encode a hy_request struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param hy_request C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_hy_request_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_hy_request_t* hy_request)
{
    return mavlink_msg_hy_request_pack(system_id, component_id, msg, hy_request->request);
}

/**
 * @brief Encode a hy_request struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param hy_request C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_hy_request_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_hy_request_t* hy_request)
{
    return mavlink_msg_hy_request_pack_chan(system_id, component_id, chan, msg, hy_request->request);
}

/**
 * @brief Encode a hy_request struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param hy_request C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_hy_request_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_hy_request_t* hy_request)
{
    return mavlink_msg_hy_request_pack_status(system_id, component_id, _status, msg,  hy_request->request);
}

/**
 * @brief Send a hy_request message
 * @param chan MAVLink channel to send the message
 *
 * @param request  (based on REQUEST_CMD_TYPES).
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_hy_request_send(mavlink_channel_t chan, uint8_t request)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HY_REQUEST_LEN];
    _mav_put_uint8_t(buf, 0, request);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_REQUEST, buf, MAVLINK_MSG_ID_HY_REQUEST_MIN_LEN, MAVLINK_MSG_ID_HY_REQUEST_LEN, MAVLINK_MSG_ID_HY_REQUEST_CRC);
#else
    mavlink_hy_request_t packet;
    packet.request = request;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_REQUEST, (const char *)&packet, MAVLINK_MSG_ID_HY_REQUEST_MIN_LEN, MAVLINK_MSG_ID_HY_REQUEST_LEN, MAVLINK_MSG_ID_HY_REQUEST_CRC);
#endif
}

/**
 * @brief Send a hy_request message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_hy_request_send_struct(mavlink_channel_t chan, const mavlink_hy_request_t* hy_request)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_hy_request_send(chan, hy_request->request);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_REQUEST, (const char *)hy_request, MAVLINK_MSG_ID_HY_REQUEST_MIN_LEN, MAVLINK_MSG_ID_HY_REQUEST_LEN, MAVLINK_MSG_ID_HY_REQUEST_CRC);
#endif
}

#if MAVLINK_MSG_ID_HY_REQUEST_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_hy_request_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t request)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, request);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_REQUEST, buf, MAVLINK_MSG_ID_HY_REQUEST_MIN_LEN, MAVLINK_MSG_ID_HY_REQUEST_LEN, MAVLINK_MSG_ID_HY_REQUEST_CRC);
#else
    mavlink_hy_request_t *packet = (mavlink_hy_request_t *)msgbuf;
    packet->request = request;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_REQUEST, (const char *)packet, MAVLINK_MSG_ID_HY_REQUEST_MIN_LEN, MAVLINK_MSG_ID_HY_REQUEST_LEN, MAVLINK_MSG_ID_HY_REQUEST_CRC);
#endif
}
#endif

#endif

// MESSAGE HY_REQUEST UNPACKING


/**
 * @brief Get field request from hy_request message
 *
 * @return  (based on REQUEST_CMD_TYPES).
 */
static inline uint8_t mavlink_msg_hy_request_get_request(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Decode a hy_request message into a struct
 *
 * @param msg The message to decode
 * @param hy_request C-struct to decode the message contents into
 */
static inline void mavlink_msg_hy_request_decode(const mavlink_message_t* msg, mavlink_hy_request_t* hy_request)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    hy_request->request = mavlink_msg_hy_request_get_request(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_HY_REQUEST_LEN? msg->len : MAVLINK_MSG_ID_HY_REQUEST_LEN;
        memset(hy_request, 0, MAVLINK_MSG_ID_HY_REQUEST_LEN);
    memcpy(hy_request, _MAV_PAYLOAD(msg), len);
#endif
}
