#ifndef MESSAGE_VIEWER_H
#define MESSAGE_VIEWER_H

#include <stdio.h>
#include "UAVTalk.h"

void PrettyPrintMessageType(FILE *f, uavtalk_message_t *msg);
void PrettyPrintObjectID(FILE *f, uavtalk_message_t *msg);
void PrettyPrintInstanceID(FILE *f, uavtalk_message_t *msg);
void PrettyPrintMessageData(FILE *f, uavtalk_message_t *msg);

void PrettyPrintMessage(FILE *f, uavtalk_message_t *msg);

#endif
