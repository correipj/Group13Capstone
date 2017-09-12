#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "UAVTalk.h"
#include "UAVTalk_Vars.h"

static unsigned long last_gcstelemetrystats_send = 0;
static unsigned long last_flighttelemetry_connect = 0;
static uint8_t telem_status = TELEMETRYSTATS_STATE_DISCONNECTED;

#ifdef EMULATE_GCS_TELEMETRY
static telemetry_stats_t telemetry_stats = {0.f, 0, 0, 0, 0.f, 0, 0, 0, 0};
#endif

// CRC lookup table
// It's more effecient to just store the 256 values rather than compute the math
// for each byte, especially to avoid computing the same values repeatedly
static const uint8_t crc_table[256] = {
	0x00, 0x07, 0x0E, 0x09, 0x1C, 0x1B, 0x12, 0x15, 0x38, 0x3F, 0x36, 0x31, 0x24, 0x23, 0x2A, 0x2d,
	0x70, 0x77, 0x7E, 0x79, 0x6C, 0x6B, 0x62, 0x65, 0x48, 0x4F, 0x46, 0x41, 0x54, 0x53, 0x5A, 0x5d,
	0xE0, 0xE7, 0xEE, 0xE9, 0xFC, 0xFB, 0xF2, 0xF5, 0xD8, 0xDF, 0xD6, 0xD1, 0xC4, 0xC3, 0xCA, 0xCd,
	0x90, 0x97, 0x9E, 0x99, 0x8C, 0x8B, 0x82, 0x85, 0xA8, 0xAF, 0xA6, 0xA1, 0xB4, 0xB3, 0xBA, 0xBd,
	0xC7, 0xC0, 0xC9, 0xCE, 0xDB, 0xDC, 0xD5, 0xD2, 0xFF, 0xF8, 0xF1, 0xF6, 0xE3, 0xE4, 0xED, 0xEa,
	0xB7, 0xB0, 0xB9, 0xBE, 0xAB, 0xAC, 0xA5, 0xA2, 0x8F, 0x88, 0x81, 0x86, 0x93, 0x94, 0x9D, 0x9a,
	0x27, 0x20, 0x29, 0x2E, 0x3B, 0x3C, 0x35, 0x32, 0x1F, 0x18, 0x11, 0x16, 0x03, 0x04, 0x0D, 0x0a,
	0x57, 0x50, 0x59, 0x5E, 0x4B, 0x4C, 0x45, 0x42, 0x6F, 0x68, 0x61, 0x66, 0x73, 0x74, 0x7D, 0x7a,
	0x89, 0x8E, 0x87, 0x80, 0x95, 0x92, 0x9B, 0x9C, 0xB1, 0xB6, 0xBF, 0xB8, 0xAD, 0xAA, 0xA3, 0xA4,
	0xF9, 0xFE, 0xF7, 0xF0, 0xE5, 0xE2, 0xEB, 0xEC, 0xC1, 0xC6, 0xCF, 0xC8, 0xDD, 0xDA, 0xD3, 0xD4,
	0x69, 0x6E, 0x67, 0x60, 0x75, 0x72, 0x7B, 0x7C, 0x51, 0x56, 0x5F, 0x58, 0x4D, 0x4A, 0x43, 0x44,
	0x19, 0x1E, 0x17, 0x10, 0x05, 0x02, 0x0B, 0x0C, 0x21, 0x26, 0x2F, 0x28, 0x3D, 0x3A, 0x33, 0x34,
	0x4E, 0x49, 0x40, 0x47, 0x52, 0x55, 0x5C, 0x5B, 0x76, 0x71, 0x78, 0x7F, 0x6A, 0x6D, 0x64, 0x63,
	0x3E, 0x39, 0x30, 0x37, 0x22, 0x25, 0x2C, 0x2B, 0x06, 0x01, 0x08, 0x0F, 0x1A, 0x1D, 0x14, 0x13,
	0xAE, 0xA9, 0xA0, 0xA7, 0xB2, 0xB5, 0xBC, 0xBB, 0x96, 0x91, 0x98, 0x9F, 0x8A, 0x8D, 0x84, 0x83,
	0xDE, 0xD9, 0xD0, 0xD7, 0xC2, 0xC5, 0xCC, 0xCB, 0xE6, 0xE1, 0xE8, 0xEF, 0xFA, 0xFD, 0xF4, 0xF3
};


// Utility functions to read integers of varying lengths and floats from the
// array of bytes in a messages data payload.
int8_t uavtalk_get_int8(uavtalk_message_t *msg, int pos) {
	return msg->data[pos];
}
uint8_t uavtalk_get_uint8(uavtalk_message_t *msg, int pos) {
	return msg->data[pos];
}
int16_t uavtalk_get_int16(uavtalk_message_t *msg, int pos) {
	int16_t i;
	memcpy(&i, msg->data+pos, sizeof(int16_t));
	return i;
}
uint16_t uavtalk_get_uint16(uavtalk_message_t *msg, int pos) {
	uint16_t i;
	memcpy(&i, msg->data+pos, sizeof(uint16_t));
	return i;
}
int32_t uavtalk_get_int32(uavtalk_message_t *msg, int pos) {
	int32_t i;
	memcpy(&i, msg->data+pos, sizeof(int32_t));
	return i;
}
uint32_t uavtalk_get_uint32(uavtalk_message_t *msg, int pos) {
	uint32_t i;
	memcpy(&i, msg->data+pos, sizeof(uint32_t));
	return i;
}
float uavtalk_get_float(uavtalk_message_t *msg, int pos) {
	float f;
	memcpy(&f, msg->data+pos, sizeof(float));
	return f;
}


// Converts a uavtalk_message_t into a string of bytes. str is assumed to have
// enough space to store the entire message, ie its length is >= msg->length+1
// calculates checksum too
int uavtalk_write_msg_str(uavtalk_message_t *msg, char *str) {
	// Sync Val
	str[0] = msg->syncChar;

	// Message Type
	str[1] = msg->msgType;

	// Length
	str[2] = (uint8_t)(msg->length & 0xFF);             // LSByte (0)
	str[3] = (uint8_t)((msg->length >> 8) & 0xFF);      // MSByte (1)    

	// Object ID
	str[4] = (uint8_t)(msg->objID & 0xFF);              // LSByte (0)
	str[5] = (uint8_t)((msg->objID >> 8) & 0xFF);       // 1
	str[6] = (uint8_t)((msg->objID >> 16) & 0xFF);      // 2
	str[7] = (uint8_t)((msg->objID >> 24) & 0xFF);      // MSByte (3)

	// Instance ID, always 0 for single instance UAVObjects
	str[8] = (uint8_t)(msg->instID & 0xFF);             // LSByte (0)
	str[9] = (uint8_t)((msg->instID >> 8) & 0xFF);      // MSByte (1)

	// Note that the header can optionally include a timestamp iff the most
	// significant bit of MesageType is set to 1. Timestamps are not included
	// in this simplified version of the UAVTalk protocol

    msg->crc = 0;
	// Update checksum from header
	for (uint8_t i = 0; i < HEADER_LEN; i++)
		msg->crc = crc_table[msg->crc ^ str[i]];

	// Copy data and update checksum from data:
	for (uint8_t i = HEADER_LEN; i < msg->length; i++) {
		str[i] = msg->data[i-HEADER_LEN];
		msg->crc = crc_table[msg->crc ^ str[i]];
	}

	// CHECKSUM:
	str[msg->length] = msg->crc;

	return msg->length + 1;     // Add one to account for the checksum byte
}

uint8_t uavtalk_make_msg_type(uint8_t kind) {
	return MESSAGE_TYPE_PROTOCOL_VER | (kind & MESSAGE_TYPE_KIND_MASK);
}

// Send a response message of a specified kind.
void uavtalk_respond_object(int fd, uavtalk_message_t *inMsg, uint8_t kind) {
	uavtalk_message_t msg;

	msg.syncChar    = UAVTALK_SYNC_VAL;
	msg.msgType     = uavtalk_make_msg_type(kind);
	msg.length      = HEADER_LEN;
	msg.objID       = inMsg->objID;
    msg.instID      = 0x0000;

	uavtalk_send_msg(fd, &msg);
}

// Returns number of bytes written
int uavtalk_send_msg(int fd, uavtalk_message_t *msg) {
    char *msgStr = (char*)malloc(msg->length + 1);
    int msgLen = uavtalk_write_msg_str(msg, msgStr);
    
    int ret = write(fd, msgStr, msgLen);
    
    free(msgStr);
    
#ifdef EMULATE_GCS_TELEMETRY
    telemetry_stats.txBytes += msgLen;
    // update txDataRate
    // update txFailures based on ret
#endif
    
    return ret;
}

// Sends ground control system telemetry info?
// Also keeps track of timing information so as not to be called too often
void uavtalk_send_gcstelemetrystats(int fd, uint8_t status) {
	uavtalk_message_t msg;

	msg.syncChar    = UAVTALK_SYNC_VAL;
	msg.msgType     = uavtalk_make_msg_type(MESSAGE_KIND_OBJ_ACK);
	msg.length      = HEADER_LEN + GCSTELEMETRYSTATS_LEN;
	msg.objID       = GCSTELEMETRYSTATS_OBJID;
    msg.instID      = 0x0000;

#ifdef EMULATE_GCS_TELEMETRY
    memset(msg.data, &telemetry_stats, sizeof(telemetry_stats));
#else
	memset(msg.data, 0, GCSTELEMETRYSTATS_LEN);
#endif
	msg.data[GCSTELEMETRYSTATS_STATUS] = status;

	uavtalk_send_msg(fd, &msg);
    
	// FIXME: replace millis()
	//last_gcstelemetrystats_send = millis();
}


// Assembles a uavtalk_message_t byte by byte.
// Returns 0 when message is incomplete or corrupted
// Returns message length on completion
uint8_t uavtalk_parse_char(uint8_t c, uavtalk_message_t *msg) {
	static uint8_t status = UAVTALK_PARSE_STATE_WAIT_SYNC;
	static uint8_t crc = 0;
	static uint8_t cnt = 0;

	switch (status) {
	case UAVTALK_PARSE_STATE_WAIT_SYNC:
		if (c == UAVTALK_SYNC_VAL) {
			status = UAVTALK_PARSE_STATE_GOT_SYNC;
			msg->syncChar = c;
			crc = crc_table[0 ^ c];
		}
		break;
	case UAVTALK_PARSE_STATE_GOT_SYNC:
		crc = crc_table[crc ^ c];
		if ((c & MESSAGE_TYPE_VER_MASK) == MESSAGE_TYPE_PROTOCOL_VER) {
			status = UAVTALK_PARSE_STATE_GOT_MSG_TYPE;
			msg->msgType = c;
			cnt = 0;
		} else {
			status = UAVTALK_PARSE_STATE_WAIT_SYNC;
		}
		break;
	case UAVTALK_PARSE_STATE_GOT_MSG_TYPE:
		crc = crc_table[crc ^ c];
		cnt++;
		if (cnt < 2) {
			msg->length = (uint16_t)c;
		} else {
			msg->length += (uint16_t)c << 8;

			if ((msg->length < HEADER_LEN) || (msg->length > 255 + HEADER_LEN)) {
                // Drop corrupted messages:
                // Minimal length is HEADER_LEN
                // Maximum is HEADER_LEN + 255 (data)
				status = UAVTALK_PARSE_STATE_WAIT_SYNC;
			} else {
				status = UAVTALK_PARSE_STATE_GOT_LENGTH;
				cnt = 0;
            }
		}
		break;
	case UAVTALK_PARSE_STATE_GOT_LENGTH:
		crc = crc_table[crc ^ c];
		cnt++;
		switch (cnt) {
		case 1:
			msg->objID = (uint32_t)c;
			break;
		case 2:
			msg->objID += (uint32_t)c << 8;
			break;
		case 3:
			msg->objID += (uint32_t)c << 16;
			break;
		case 4:
			msg->objID += (uint32_t)c << 24;
			status = UAVTALK_PARSE_STATE_GOT_OBJID;
			cnt = 0;
			break;
		}
		break;
	case UAVTALK_PARSE_STATE_GOT_OBJID:
		crc = crc_table[crc ^ c];
		cnt++;
		switch (cnt) {
		case 1:
			msg->instID = (uint32_t)c;
			break;
		case 2:
			msg->instID += (uint32_t)c << 8;

			// If message doesn't include any data, skip over data recording step
			if (msg->length == HEADER_LEN)
				status = UAVTALK_PARSE_STATE_GOT_DATA;
			else
				status = UAVTALK_PARSE_STATE_GOT_INSTID;

			cnt = 0;
			break;
		}
		break;
	case UAVTALK_PARSE_STATE_GOT_INSTID:
		crc = crc_table[crc ^ c];
		cnt++;
		msg->data[cnt - 1] = c;

		if (cnt >= msg->length - HEADER_LEN) {
			status = UAVTALK_PARSE_STATE_GOT_DATA;
			cnt = 0;
		}

		break;
	case UAVTALK_PARSE_STATE_GOT_DATA:
		msg->crc = c;
		status = UAVTALK_PARSE_STATE_GOT_CRC;
		break;
	}

	// If we have received a full message
	if (status == UAVTALK_PARSE_STATE_GOT_CRC) {
		status = UAVTALK_PARSE_STATE_WAIT_SYNC;
        
#ifdef EMULATE_GCS_TELEMETRY
        // update received bytes
        telemetry_stats.rxBytes += msg->length+1;
#endif

		if (crc == msg->crc)
			return msg->length;
		else {
			// Non-matching CRC
#ifdef EMULATE_GCS_TELEMETRY
            telemetry_stats.rxCrcErrors++;
#endif
			return 0;
        }
	}

	// Haven't yet received full message
	return 0;
}

// Return 1 when message was consumed, else return 0
int uavtalk_handle_msg(int fd, uavtalk_message_t *msg) {
    switch(msg->objID) {
	case FLIGHTTELEMETRYSTATS_OBJID:
        // ACK current message
        uavtalk_respond_object(fd, msg, MESSAGE_KIND_ACK);
    
        switch (msg->data[FLIGHTTELEMETRYSTATS_STATUS]) {
		case TELEMETRYSTATS_STATE_DISCONNECTED:
			telem_status = TELEMETRYSTATS_STATE_HANDSHAKEREQ;
			uavtalk_send_gcstelemetrystats(fd, TELEMETRYSTATS_STATE_HANDSHAKEREQ);
			break;
		case TELEMETRYSTATS_STATE_HANDSHAKEACK:
			telem_status = TELEMETRYSTATS_STATE_CONNECTED;
			uavtalk_send_gcstelemetrystats(fd, TELEMETRYSTATS_STATE_CONNECTED);
			break;
		case TELEMETRYSTATS_STATE_CONNECTED:
			telem_status = TELEMETRYSTATS_STATE_CONNECTED;
			break;
		}
		return 1;
    default:
        return 0;
    }
}

int uavtalk_telem_state(void) {
	return telem_status;
}
