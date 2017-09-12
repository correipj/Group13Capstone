#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringSerial.h>

#include "UAVTalk.h"
#include "MessageViewer.h"
#include "AllObjs.h"

int fd;

void sendReqMsg(uint32_t objid) {
    uavtalk_message_t msg;

    msg.syncChar    = UAVTALK_SYNC_VAL;
    msg.msgType     = uavtalk_make_msg_type(MESSAGE_KIND_REQ);
    msg.length      = HEADER_LEN;
    msg.objID       = objid;
    msg.instID      = 0x0000;
    
    uavtalk_send_msg(fd, &msg);
}

int main (int argc, char **argv) {
    int baud = 57600;

    if ((fd = serialOpen("/dev/ttyAMA0", baud)) < 0) {
        fprintf(stderr, "Unable to open \"/dev/ttyAMA0\"\n");
        return 1;
    }

    uavtalk_message_t inMsg;
    uint32_t currObjID = 0;
    int currObjIDNum = -1;
    const int numObjs = 109;
    
    int nMsgs = 101;
    const int maxNMsgs = 50;
    
    const char* respStr[5] = {"OBJ", "REQ", "OBJ ACK", "ACK", "NACK"};

    while (currObjIDNum < numObjs) {
        while(serialDataAvail(fd) > 0) {
            char c = serialGetchar(fd);

            if (uavtalk_parse_char(c, &inMsg)) {
                if (uavtalk_handle_msg(fd, &inMsg))
                    continue;
                
                if (uavtalk_telem_state() != TELEMETRYSTATS_STATE_CONNECTED)
                    continue;                
                
                nMsgs++;
                
                // If the incoming message matches the requested object
                // OR if we are finished waiting for a response
                // record response and request next object
                if (inMsg.objID == currObjID || nMsgs > maxNMsgs) {
                    PrettyPrintObjectID(stdout, &inMsg);
                    
                    uint8_t response = inMsg.msgType & MESSAGE_TYPE_KIND_MASK;
                    if (response <= 0x04)
                        printf(" responded with %s\n", respStr[response]);
                    else
                        printf(" did not respond\n");
                
                    // Request next object
                    nMsgs = 0;
                    currObjIDNum++;
                    currObjID = objids[currObjIDNum];
                    
                    sendReqMsg(currObjID);                    
                }
            }
        }
    }

    return 0;
}
