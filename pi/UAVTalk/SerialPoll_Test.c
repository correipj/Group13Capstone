
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringSerial.h>

#include "UAVTalk.h"
#include "MessageViewer.h"

#include "AllObjs.h"

void printMsg(uavtalk_message_t inMsg) {
	if (inMsg.syncChar != UAVTALK_SYNC_VAL) {
		printf("fuck this\n");
		return;
	}

	printf("Sync    = 0x%02X\n", inMsg.syncChar);
	printf("MsgType = 0x%02X\n", inMsg.msgType);
	printf("Length  = %d\n", inMsg.length);
	printf("ObjID   = 0x%08X\n", inMsg.objID);
	printf("InstID  = %lu\n", inMsg.instID);
	printf("Data = [");

	int i;

	for (i = 0; i < inMsg.length - HEADER_LEN; i++)
		printf("0x%02X\n", inMsg.data[i]);

	printf("]\n");
}

uavtalk_message_t makeAckMsg() {
	uavtalk_message_t msg;
	
	msg.syncChar	= UAVTALK_SYNC_VAL;
	msg.msgType		= uavtalk_make_msg_type(MESSAGE_KIND_OBJ_ACK);
	msg.length		= 30;
	msg.objID		= GCSTELEMETRYSTATS_OBJID_001;
	msg.instID		= 0x0;
	memset(msg.data, 0, 22);
	
	return msg;
}

void handleMsg(uavtalk_message_t inMsg) {
	static int handshakeState = 0;
}

int main (int argc, char **argv) {
	int fd;
	int baud = 57600;

	if ((fd = serialOpen("/dev/ttyAMA0", baud)) < 0) {
		fprintf(stderr, "Unable to open \"/dev/ttyAMA0\"\n");
		return 1;
	}

	if (wiringPiSetup() == -1) {
		fprintf(stderr, "unable to init wiringPi\n");
		return 1;
	}
	
	// Send out an ACK message:
	uavtalk_message_t outMsg = makeAckMsg();
	char* outMsgStr = (char*)malloc(266);
	int outMsgN;
	
	uavtalk_message_t inMsg;
	
	int n = 0;
	while (n < 110) {
		outMsg.objID = objids[n];
		printf("Test OBJID = 0x%08X\n", outMsg.objID);
		
		outMsgN = uavtalk_write_msg_str(&outMsg, outMsgStr);
		
		write(fd, outMsgStr, outMsgN);
		
		delay(500);
		
		while(serialDataAvail(fd) > 0) {
			char c = serialGetchar(fd);

			printf("%02X ", c);

			if (uavtalk_parse_char(c, &inMsg)) {
				PrettyPrintMessage(stdout, inMsg);
			}
		}
		n++;
	}
	
	free(outMsgStr);
	
	return 0;
}
