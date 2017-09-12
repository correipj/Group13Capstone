#ifndef UAVTALK_H
#define UAVTALK_H

#include <stdint.h>
#include "UAVTalk_Config.h"
#include "UAVTalk_Objects.h"

#define HEADER_LEN                          10

#define UAVTALK_SYNC_VAL                    0x3C        // First byte of a UAVTalk message

#define MESSAGE_TYPE_VER_MASK               0x70        // Bits where protocol version is stored in Message Type
#define MESSAGE_TYPE_PROTOCOL_VER           0x20        // UAVTalk Protocal Version (Bits 5-7)
#define MESSAGE_TYPE_TIMESTAMP_MASK         0x80        // Bit that indicates a timestamped message

#define MESSAGE_TYPE_KIND_MASK              0x0F        // Bits where kind of message is stored in Message Type
#define MESSAGE_KIND_OBJ                    0x00        // Object Data
#define MESSAGE_KIND_REQ                    0x01        // Object Request
#define MESSAGE_KIND_OBJ_ACK                0x02        // Object with acknowledge request
#define MESSAGE_KIND_ACK                    0x03        // Acknowledge
#define MESSAGE_KIND_NACK                   0x04        // Negative Acknowledge

typedef enum {
    UAVTALK_PARSE_STATE_WAIT_SYNC = 0,
    UAVTALK_PARSE_STATE_GOT_SYNC,
    UAVTALK_PARSE_STATE_GOT_MSG_TYPE,
    UAVTALK_PARSE_STATE_GOT_LENGTH,
    UAVTALK_PARSE_STATE_GOT_OBJID,
    UAVTALK_PARSE_STATE_GOT_INSTID,
    UAVTALK_PARSE_STATE_GOT_DATA,
    UAVTALK_PARSE_STATE_GOT_CRC
} uavtalk_parse_state_t;


typedef enum {
    TELEMETRYSTATS_STATE_DISCONNECTED = 0,
    TELEMETRYSTATS_STATE_HANDSHAKEREQ,
    TELEMETRYSTATS_STATE_HANDSHAKEACK,
    TELEMETRYSTATS_STATE_CONNECTED
} telemetry_state_t;


typedef struct {
    uint8_t syncChar;
    uint8_t msgType;
    uint16_t length;
    uint32_t objID;
    uint16_t instID;
    uint8_t data[255];
    uint8_t crc;
} uavtalk_message_t;


#ifdef EMULATE_GCS_TELEMETRY

typedef struct {
    float txDataRate;
    uint32_t txBytes;
    uint32_t txFailures;
    uint32_t txRetries;
    float rxDataRate;
    uint32_t rxBytes;
    uint32_t rxFailures;
    uint32_t rxSyncErrors;
    uint32_t rxCrcErrors;
} telemetry_stats_t;

#endif

int8_t uavtalk_get_int8(uavtalk_message_t *msg, int pos);
uint8_t uavtalk_get_uint8(uavtalk_message_t *msg, int pos);
int16_t uavtalk_get_int16(uavtalk_message_t *msg, int pos);
uint16_t uavtalk_get_uint16(uavtalk_message_t *msg, int pos);
int32_t uavtalk_get_int32(uavtalk_message_t *msg, int pos);
uint32_t uavtalk_get_uint32(uavtalk_message_t *msg, int pos);
float uavtalk_get_float(uavtalk_message_t *msg, int pos);

int uavtalk_write_msg_str(uavtalk_message_t *msg, char *str);
uint8_t uavtalk_make_msg_type(uint8_t kind);
int uavtalk_send_msg(int fd, uavtalk_message_t *msg);
uint8_t uavtalk_parse_char(uint8_t c, uavtalk_message_t *inMsg);
int uavtalk_handle_msg(int fd, uavtalk_message_t *msg);
int uavtalk_telem_state(void);

#endif
