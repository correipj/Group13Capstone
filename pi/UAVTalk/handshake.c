#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringSerial.h>

#include "UAVTalk.h"
#include "MessageViewer.h"

int fd;

int main (int argc, char **argv) {
    int baud = 57600;

    if ((fd = serialOpen("/dev/ttyAMA0", baud)) < 0) {
        fprintf(stderr, "Unable to open \"/dev/ttyAMA0\"\n");
        return 1;
    }

    uavtalk_message_t inMsg;

    while (1) {
        while(serialDataAvail(fd) > 0) {
            char c = serialGetchar(fd);

            if (uavtalk_parse_char(c, &inMsg)) {                
                if (uavtalk_handle_msg(fd, &inMsg)) {
                    printf("status = %d\n", uavtalk_telem_state());
                }
            }
        }
    }

    return 0;
}
