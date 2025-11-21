#pragma once
// MESSAGE HY_GIMBAL_CAMERA PACKING

#define MAVLINK_MSG_ID_HY_GIMBAL_CAMERA 11060


typedef struct __mavlink_hy_gimbal_camera_t {
 uint8_t fun_type; /*<  (based enum CAMERA_FUNCTION_TYPE,).*/
 uint8_t cmd_status; /*<  (based enum CAMERA_CMD_STATUS).*/
} mavlink_hy_gimbal_camera_t;

#define MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_LEN 2
#define MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_MIN_LEN 2
#define MAVLINK_MSG_ID_11060_LEN 2
#define MAVLINK_MSG_ID_11060_MIN_LEN 2

#define MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_CRC 27
#define MAVLINK_MSG_ID_11060_CRC 27



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_HY_GIMBAL_CAMERA { \
    11060, \
    "HY_GIMBAL_CAMERA", \
    2, \
    {  { "fun_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_hy_gimbal_camera_t, fun_type) }, \
         { "cmd_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_hy_gimbal_camera_t, cmd_status) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_HY_GIMBAL_CAMERA { \
    "HY_GIMBAL_CAMERA", \
    2, \
    {  { "fun_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_hy_gimbal_camera_t, fun_type) }, \
         { "cmd_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_hy_gimbal_camera_t, cmd_status) }, \
         } \
}
#endif

/**
 * @brief Pack a hy_gimbal_camera message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param fun_type  (based enum CAMERA_FUNCTION_TYPE,).
 * @param cmd_status  (based enum CAMERA_CMD_STATUS).
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_hy_gimbal_camera_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t fun_type, uint8_t cmd_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_LEN];
    _mav_put_uint8_t(buf, 0, fun_type);
    _mav_put_uint8_t(buf, 1, cmd_status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_LEN);
#else
    mavlink_hy_gimbal_camera_t packet;
    packet.fun_type = fun_type;
    packet.cmd_status = cmd_status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_HY_GIMBAL_CAMERA;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_CRC);
}

/**
 * @brief Pack a hy_gimbal_camera message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param fun_type  (based enum CAMERA_FUNCTION_TYPE,).
 * @param cmd_status  (based enum CAMERA_CMD_STATUS).
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_hy_gimbal_camera_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint8_t fun_type, uint8_t cmd_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_LEN];
    _mav_put_uint8_t(buf, 0, fun_type);
    _mav_put_uint8_t(buf, 1, cmd_status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_LEN);
#else
    mavlink_hy_gimbal_camera_t packet;
    packet.fun_type = fun_type;
    packet.cmd_status = cmd_status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_HY_GIMBAL_CAMERA;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_LEN);
#endif
}

/**
 * @brief Pack a hy_gimbal_camera message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param fun_type  (based enum CAMERA_FUNCTION_TYPE,).
 * @param cmd_status  (based enum CAMERA_CMD_STATUS).
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_hy_gimbal_camera_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t fun_type,uint8_t cmd_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_LEN];
    _mav_put_uint8_t(buf, 0, fun_type);
    _mav_put_uint8_t(buf, 1, cmd_status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_LEN);
#else
    mavlink_hy_gimbal_camera_t packet;
    packet.fun_type = fun_type;
    packet.cmd_status = cmd_status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_HY_GIMBAL_CAMERA;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_CRC);
}

/**
 * @brief Encode a hy_gimbal_camera struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param hy_gimbal_camera C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_hy_gimbal_camera_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_hy_gimbal_camera_t* hy_gimbal_camera)
{
    return mavlink_msg_hy_gimbal_camera_pack(system_id, component_id, msg, hy_gimbal_camera->fun_type, hy_gimbal_camera->cmd_status);
}

/**
 * @brief Encode a hy_gimbal_camera struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param hy_gimbal_camera C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_hy_gimbal_camera_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_hy_gimbal_camera_t* hy_gimbal_camera)
{
    return mavlink_msg_hy_gimbal_camera_pack_chan(system_id, component_id, chan, msg, hy_gimbal_camera->fun_type, hy_gimbal_camera->cmd_status);
}

/**
 * @brief Encode a hy_gimbal_camera struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param hy_gimbal_camera C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_hy_gimbal_camera_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_hy_gimbal_camera_t* hy_gimbal_camera)
{
    return mavlink_msg_hy_gimbal_camera_pack_status(system_id, component_id, _status, msg,  hy_gimbal_camera->fun_type, hy_gimbal_camera->cmd_status);
}

/**
 * @brief Send a hy_gimbal_camera message
 * @param chan MAVLink channel to send the message
 *
 * @param fun_type  (based enum CAMERA_FUNCTION_TYPE,).
 * @param cmd_status  (based enum CAMERA_CMD_STATUS).
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_hy_gimbal_camera_send(mavlink_channel_t chan, uint8_t fun_type, uint8_t cmd_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_LEN];
    _mav_put_uint8_t(buf, 0, fun_type);
    _mav_put_uint8_t(buf, 1, cmd_status);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA, buf, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_CRC);
#else
    mavlink_hy_gimbal_camera_t packet;
    packet.fun_type = fun_type;
    packet.cmd_status = cmd_status;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA, (const char *)&packet, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_CRC);
#endif
}

/**
 * @brief Send a hy_gimbal_camera message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_hy_gimbal_camera_send_struct(mavlink_channel_t chan, const mavlink_hy_gimbal_camera_t* hy_gimbal_camera)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_hy_gimbal_camera_send(chan, hy_gimbal_camera->fun_type, hy_gimbal_camera->cmd_status);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA, (const char *)hy_gimbal_camera, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_CRC);
#endif
}

#if MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_hy_gimbal_camera_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t fun_type, uint8_t cmd_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, fun_type);
    _mav_put_uint8_t(buf, 1, cmd_status);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA, buf, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_CRC);
#else
    mavlink_hy_gimbal_camera_t *packet = (mavlink_hy_gimbal_camera_t *)msgbuf;
    packet->fun_type = fun_type;
    packet->cmd_status = cmd_status;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA, (const char *)packet, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_MIN_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_LEN, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_CRC);
#endif
}
#endif

#endif

// MESSAGE HY_GIMBAL_CAMERA UNPACKING


/**
 * @brief Get field fun_type from hy_gimbal_camera message
 *
 * @return  (based enum CAMERA_FUNCTION_TYPE,).
 */
static inline uint8_t mavlink_msg_hy_gimbal_camera_get_fun_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field cmd_status from hy_gimbal_camera message
 *
 * @return  (based enum CAMERA_CMD_STATUS).
 */
static inline uint8_t mavlink_msg_hy_gimbal_camera_get_cmd_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Decode a hy_gimbal_camera message into a struct
 *
 * @param msg The message to decode
 * @param hy_gimbal_camera C-struct to decode the message contents into
 */
static inline void mavlink_msg_hy_gimbal_camera_decode(const mavlink_message_t* msg, mavlink_hy_gimbal_camera_t* hy_gimbal_camera)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    hy_gimbal_camera->fun_type = mavlink_msg_hy_gimbal_camera_get_fun_type(msg);
    hy_gimbal_camera->cmd_status = mavlink_msg_hy_gimbal_camera_get_cmd_status(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_LEN? msg->len : MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_LEN;
        memset(hy_gimbal_camera, 0, MAVLINK_MSG_ID_HY_GIMBAL_CAMERA_LEN);
    memcpy(hy_gimbal_camera, _MAV_PAYLOAD(msg), len);
#endif
}
