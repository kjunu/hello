/**
 * @file    test.h
 * @brief   TODO brief documentation here.
 *
 * @author
 * @version $Id$
 */

/**
 *    Packet Return Code
 */
enum {
    BS2_PROTO_SUCCESS           = 0x00,
    BS2_PROTO_ACK               = 0x01,
    BS2_PROTO_BUSY = 0x02,

    BS2_PROTO_UNSUPPORTED       = 0x100,
    BS2_PROTO_INVALID_OPTION    = 0x101,
    BS2_PROTO_INVALID_PAYLOAD   = 0x102,
    BS2_PROTO_DUPLICATED_USER   = 0x103,
    BS2_PROTO_USER_FULL         = 0x104,
    BS2_PROTO_USER_DB_ERROR     = 0x105,
    BS2_PROTO_NO_USER           = 0x106,
    BS2_PROTO_CANNOT_READ_LOG   = 0x107,
    BS2_PROTO_ROOT_CA_CERT_EXIST = 0x108,
    BS2_PROTO_INVALID_ROOT_CA_CERT = 0x109,

    /* Device Zone
     */
    BS2_PROTO_NO_MEMBER         = 0x10A,
    BS2_PROTO_NO_REGISTERED     = 0x10B,
    BS2_PROTO_APB_HARD_FAIL     = 0x10C,
    BS2_PROTO_APB_SOFT_FAIL     = 0x10D,
    BS2_PROTO_ENTRANCE_LIMIT_HARD_COUNT_FAIL        = 0x10E,
    BS2_PROTO_ENTRANCE_LIMIT_SOFT_COUNT_FAIL        = 0x10F,
    BS2_PROTO_ENTRANCE_LIMIT_HARD_TIME_FAIL         = 0x110,
    BS2_PROTO_ENTRANCE_LIMIT_SOFT_TIME_FAIL         = 0x111,
    BS2_PROTO_INVAILD_ZONE_ID   = 0x112,
};
#ifndef _test_H
#define _test_H

typedef uint32_t BS2_PACKET_START;
typedef uint16_t BS2_PACKET_SEQ;
typedef uint16_t BS2_PACKET_INDEX;
typedef uint16_t BS2_PACKET_TOTAL;
typedef uint16_t BS2_PACKET_OPTION;
typedef uint16_t BS2_PACKET_CODE;
typedef uint8_t BS2_PACKET_VER;
typedef uint32_t BS2_PACKET_PARAM;
typedef uint32_t BS2_PACKET_SIZE;
typedef uint32_t BS2_PACKET_CHECKSUM;
/**
 *   Type definition of Packet Header
 */
typedef struct {
    BS2_PACKET_START    startCode;      ///< start code of packet
    BS2_PACKET_CHECKSUM checksum;       ///< checksum for packet data except first 8 bytes
    BS2_DEVICE_ID       id;             ///< device id
    union {
        BS2_PACKET_FLAG flag;           ///< flag of packet: @ref BS2_PACKET_FLAG_
        struct {
            BS2_PACKET_FLAG encrypted: 1;
            BS2_PACKET_FLAG response: 1;
            BS2_PACKET_FLAG more: 1;
            BS2_PACKET_FLAG reserved: 5;
        };
    };
    BS2_PACKET_VER      version;        ///< version of protocol
    BS2_PACKET_SEQ      sequence;       ///< sequence of packet
    BS2_PACKET_INDEX    index;          ///< index number of continuous packet
    BS2_PACKET_TOTAL    total;          ///< total number of continuous packet
    BS2_PACKET_SIZE     payloadSize;    ///< size of payload
    union {
        BS2_PACKET_OPTION   option;     ///< will be used for request packet
        BS2_PACKET_CODE     code;       ///< will be used for response packet
    };
    BS2_PACKET_CMD      command;        ///< command: @ref BS2_PACKET_CMD
    BS2_PACKET_PARAM    param1;         ///< first parameter    : varies for each command
    BS2_PACKET_PARAM    param2;         ///< second parameter   : varies for each command
} BS2PacketHeader;

#endif /* _test_H */

