#pragma once
// MESSAGE ANADRONE PACKING

#define MAVLINK_MSG_ID_ANADRONE 1


typedef struct __mavlink_anadrone_t {
 char FIELD1; /*<  char*/
} mavlink_anadrone_t;

#define MAVLINK_MSG_ID_ANADRONE_LEN 1
#define MAVLINK_MSG_ID_ANADRONE_MIN_LEN 1
#define MAVLINK_MSG_ID_1_LEN 1
#define MAVLINK_MSG_ID_1_MIN_LEN 1

#define MAVLINK_MSG_ID_ANADRONE_CRC 214
#define MAVLINK_MSG_ID_1_CRC 214



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_ANADRONE { \
    1, \
    "ANADRONE", \
    1, \
    {  { "FIELD1", NULL, MAVLINK_TYPE_CHAR, 0, 0, offsetof(mavlink_anadrone_t, FIELD1) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_ANADRONE { \
    "ANADRONE", \
    1, \
    {  { "FIELD1", NULL, MAVLINK_TYPE_CHAR, 0, 0, offsetof(mavlink_anadrone_t, FIELD1) }, \
         } \
}
#endif

/**
 * @brief Pack a anadrone message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param FIELD1  char
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_anadrone_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               char FIELD1)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ANADRONE_LEN];
    _mav_put_char(buf, 0, FIELD1);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ANADRONE_LEN);
#else
    mavlink_anadrone_t packet;
    packet.FIELD1 = FIELD1;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ANADRONE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ANADRONE;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ANADRONE_MIN_LEN, MAVLINK_MSG_ID_ANADRONE_LEN, MAVLINK_MSG_ID_ANADRONE_CRC);
}

/**
 * @brief Pack a anadrone message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param FIELD1  char
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_anadrone_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   char FIELD1)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ANADRONE_LEN];
    _mav_put_char(buf, 0, FIELD1);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ANADRONE_LEN);
#else
    mavlink_anadrone_t packet;
    packet.FIELD1 = FIELD1;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ANADRONE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ANADRONE;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ANADRONE_MIN_LEN, MAVLINK_MSG_ID_ANADRONE_LEN, MAVLINK_MSG_ID_ANADRONE_CRC);
}

/**
 * @brief Encode a anadrone struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param anadrone C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_anadrone_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_anadrone_t* anadrone)
{
    return mavlink_msg_anadrone_pack(system_id, component_id, msg, anadrone->FIELD1);
}

/**
 * @brief Encode a anadrone struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param anadrone C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_anadrone_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_anadrone_t* anadrone)
{
    return mavlink_msg_anadrone_pack_chan(system_id, component_id, chan, msg, anadrone->FIELD1);
}

/**
 * @brief Send a anadrone message
 * @param chan MAVLink channel to send the message
 *
 * @param FIELD1  char
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_anadrone_send(mavlink_channel_t chan, char FIELD1)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ANADRONE_LEN];
    _mav_put_char(buf, 0, FIELD1);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ANADRONE, buf, MAVLINK_MSG_ID_ANADRONE_MIN_LEN, MAVLINK_MSG_ID_ANADRONE_LEN, MAVLINK_MSG_ID_ANADRONE_CRC);
#else
    mavlink_anadrone_t packet;
    packet.FIELD1 = FIELD1;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ANADRONE, (const char *)&packet, MAVLINK_MSG_ID_ANADRONE_MIN_LEN, MAVLINK_MSG_ID_ANADRONE_LEN, MAVLINK_MSG_ID_ANADRONE_CRC);
#endif
}

/**
 * @brief Send a anadrone message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_anadrone_send_struct(mavlink_channel_t chan, const mavlink_anadrone_t* anadrone)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_anadrone_send(chan, anadrone->FIELD1);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ANADRONE, (const char *)anadrone, MAVLINK_MSG_ID_ANADRONE_MIN_LEN, MAVLINK_MSG_ID_ANADRONE_LEN, MAVLINK_MSG_ID_ANADRONE_CRC);
#endif
}

#if MAVLINK_MSG_ID_ANADRONE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_anadrone_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  char FIELD1)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_char(buf, 0, FIELD1);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ANADRONE, buf, MAVLINK_MSG_ID_ANADRONE_MIN_LEN, MAVLINK_MSG_ID_ANADRONE_LEN, MAVLINK_MSG_ID_ANADRONE_CRC);
#else
    mavlink_anadrone_t *packet = (mavlink_anadrone_t *)msgbuf;
    packet->FIELD1 = FIELD1;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ANADRONE, (const char *)packet, MAVLINK_MSG_ID_ANADRONE_MIN_LEN, MAVLINK_MSG_ID_ANADRONE_LEN, MAVLINK_MSG_ID_ANADRONE_CRC);
#endif
}
#endif

#endif

// MESSAGE ANADRONE UNPACKING


/**
 * @brief Get field FIELD1 from anadrone message
 *
 * @return  char
 */
static inline char mavlink_msg_anadrone_get_FIELD1(const mavlink_message_t* msg)
{
    return _MAV_RETURN_char(msg,  0);
}

/**
 * @brief Decode a anadrone message into a struct
 *
 * @param msg The message to decode
 * @param anadrone C-struct to decode the message contents into
 */
static inline void mavlink_msg_anadrone_decode(const mavlink_message_t* msg, mavlink_anadrone_t* anadrone)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    anadrone->FIELD1 = mavlink_msg_anadrone_get_FIELD1(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_ANADRONE_LEN? msg->len : MAVLINK_MSG_ID_ANADRONE_LEN;
        memset(anadrone, 0, MAVLINK_MSG_ID_ANADRONE_LEN);
    memcpy(anadrone, _MAV_PAYLOAD(msg), len);
#endif
}
