#include <stdio.h>
#include <string.h>
#include "MessageViewer.h"

const char* typeName[5] = {"OBJ DATA", "OBJ REQ", "OBJ ACK REQ", "ACK", "NACK"};
const char* telemStateName[4] = {"Disconnected", "HandshakeREQ", "HandshakeACK", "Connected"};
const char* enStr[2] = {"Disabled", "Enabled"};


void PrettyPrintMessageType(FILE *f, uavtalk_message_t *msg) {
    fprintf(f, "Type = %s", typeName[msg->msgType & MESSAGE_TYPE_KIND_MASK]);
}
void PrettyPrintObjectID(FILE *f, uavtalk_message_t *msg) {
	fprintf(f, "ObjectID = ");

	switch(msg->objID) {
    case ACCELGYROSETTINGS_OBJID:
        fprintf(f, "ACCELGYROSETTINGS");
		break;
	case ACCELSTATE_OBJID:
		fprintf(f, "ACCELSTATE");
		break;
    case ACCESSORYDESIRED_OBJID:
		fprintf(f, "ACCESSORYDESIRED");
		break;
    case ACTUATORCOMMAND_OBJID:
		fprintf(f, "ACTUATORCOMMAND");
		break;
	case ACTUATORDESIRED_OBJID:
		fprintf(f, "ACTUATORDESIRED");
		break;
    case ACTUATORSETTINGS_OBJID:
        fprintf(f, "ACTUATORSETTINGS");
		break;
    case ATTITUDESETTINGS_OBJID:
        fprintf(f, "ATTITUDESETTINGS");
		break;
    case ATTITUDESTATE_OBJID:
		fprintf(f, "ATTITUDESTATE");
		break;
    case FIRMWAREIAPOBJ_OBJID:
        fprintf(f, "FIRMWAREIAPOBJ");
		break;
    case FLIGHTMODESETTINGS_OBJID:
        fprintf(f, "FLIGHTMODESETTINGS");
		break;
	case FLIGHTTELEMETRYSTATS_OBJID:
		fprintf(f, "FLIGHTTELEMETRYSTATS");
		break;
	case FLIGHTSTATUS_OBJID:
		fprintf(f, "FLIGHTSTATUS");
		break;
    case GCSTELEMETRYSTATS_OBJID:
		fprintf(f, "GCSTELEMETRYSTATS");
		break;
	case GYROSTATE_OBJID:
		fprintf(f, "GYROSTATE");
		break;
	case GPSPOSITIONSENSOR_OBJID:
		fprintf(f, "GPSPOSITIONSENSOR");
		break;
	case GPSTIME_OBJID:
		fprintf(f, "GPSTIME");
		break;
	case GPSVELOCITYSENSOR_OBJID:
		fprintf(f, "GPSVELOCITYSENSOR");
		break;
    case HWSETTINGS_OBJID:
		fprintf(f, "HWSETTINGS");
		break;
    case MANUALCONTROLCOMMAND_OBJID:
		fprintf(f, "MANUALCONTROLCOMMAND");
		break;
    case MANUALCONTROLSETTINGS_OBJID:
		fprintf(f, "MANUALCONTROLSETTINGS");
		break;
    case MIXERSETTINGS_OBJID:
		fprintf(f, "MIXERSETTINGS");
		break;
    case MPUGYROACCELSETTINGS_OBJID:
		fprintf(f, "MPUGYROACCELSETTINGS");
		break;
    case OBJECTPERSISTENCE_OBJID:
		fprintf(f, "OBJECTPERSISTENCE");
		break;
	case RATEDESIRED_OBJID:
		fprintf(f, "RATEDESIRED");
		break;
	case RECEIVERACTIVITY_OBJID:
		fprintf(f, "RECEIVERACTIVITY");
		break;
    case RECEIVERSTATUS_OBJID:
		fprintf(f, "RECEIVERSTATUS");
		break;
	case STABILIZATIONBANK_OBJID:
		fprintf(f, "STABILIZATIONBANK");
		break;
	case STABILIZATIONDESIRED_OBJID:
		fprintf(f, "STABILIZATIONDESIRED");
		break;
	case STABILIZATIONSETTINGS_OBJID:
		fprintf(f, "STABILIZATIONSETTINGS");
		break;
    case STABILIZATIONSETTINGSBANK1_OBJID:
		fprintf(f, "STABILIZATIONSETTINGSBANK1");
		break;
    case STABILIZATIONSETTINGSBANK2_OBJID:
		fprintf(f, "STABILIZATIONSETTINGSBANK2");
		break;
    case STABILIZATIONSETTINGSBANK3_OBJID:
		fprintf(f, "STABILIZATIONSETTINGSBANK3");
		break;
    case STABILIZATIONSTATUS_OBJID:
		fprintf(f, "STABILIZATIONSTATUS");
		break;
	case SYSTEMALARMS_OBJID:
		fprintf(f, "SYSTEMALARMS");
		break;
    case SYSTEMSETTINGS_OBJID:
		fprintf(f, "SYSTEMSETTINGS");
		break;
	case SYSTEMSTATS_OBJID:
		fprintf(f, "SYSTEMSTATS");
		break;
	default:
		fprintf(f, "0x%08X", msg->objID);
		break;
	}
}
void PrettyPrintInstanceID(FILE *f, uavtalk_message_t *msg) {
    fprintf(f, "Instance = 0x%04X", msg->instID);
}


void PrettyPrintFlightTelemStats(FILE *f, uavtalk_message_t *msg) {
    fprintf(f, "TxDataRate:%8.2f\n", uavtalk_get_float(msg, 0));
    fprintf(f, "TxBytes:%11d\n", uavtalk_get_int32(msg, 4));
    fprintf(f, "TxFailures:%8d\n", uavtalk_get_int32(msg, 8));
    fprintf(f, "TxRetries:%9d\n", uavtalk_get_int32(msg, 12));
    fprintf(f, "RxDataRate:%8.2f\n", uavtalk_get_float(msg, 16));
    fprintf(f, "RxDataBytes:%7d\n", uavtalk_get_int32(msg, 20));
    fprintf(f, "RxFailures:%8d\n", uavtalk_get_int32(msg, 24));
    fprintf(f, "RxSyncErrors:%6d\n", uavtalk_get_int32(msg, 28));
    fprintf(f, "RxCrcErrors:%7d\n", uavtalk_get_int32(msg, 32));
    fprintf(f, "State = %s\n", telemStateName[msg->data[FLIGHTTELEMETRYSTATS_STATUS]]);
}
void PrettyPrintGCSTelemStats(FILE *f, uavtalk_message_t *msg) {
    fprintf(f, "State = %s\n", telemStateName[msg->data[GCSTELEMETRYSTATS_STATUS]]);
}

void PrettyPrintAccelState(FILE *f, uavtalk_message_t *msg) {
    fprintf(f, "XYZ = {%f %f %f} m/s^2\n", 
        uavtalk_get_float(msg, ACCELSTATE_X),
        uavtalk_get_float(msg, ACCELSTATE_Y),
        uavtalk_get_float(msg, ACCELSTATE_Z));
}
void PrettyPrintAccessoryDesired(FILE *f, uavtalk_message_t *msg) {
    fprintf(f, "Accessory Value = %f\n", uavtalk_get_float(msg, ACCESSORYDESIRED_ACCESSORY));
}
void PrettyPrintActuatorCommand(FILE *f, uavtalk_message_t *msg) {
    for (int i = 0; i < ACTUATORCOMMAND_NUM_CHANNELS; i++)
        fprintf(f, "CHANNEL%02d = %d us\n", i, uavtalk_get_int16(msg, ACTUATORCOMMAND_CHANNEL0 + i*2));
    
    fprintf(f, "UPDATE TIME = %d ms\n", uavtalk_get_uint16(msg, ACTUATORCOMMAND_UPDATE_TIME));
    
    fprintf(f, "MAX UPDATE TIME = %d ms\n", uavtalk_get_uint16(msg, ACTUATORCOMMAND_MAX_UPDATE_TIME));    
    
    fprintf(f, "NUM FAILED UPDATES = %d\n", uavtalk_get_uint8(msg, ACTUATORCOMMAND_NUM_FAILED_UPDATES));
}
void PrettyPrintActuatorDesired(FILE *f, uavtalk_message_t *msg) {
    fprintf(f, "PYRT = {%f %f %f %f} %%\n",
        uavtalk_get_float(msg, ACTUATORDESIRED_PITCH),
        uavtalk_get_float(msg, ACTUATORDESIRED_YAW),
        uavtalk_get_float(msg, ACTUATORDESIRED_ROLL),
        uavtalk_get_float(msg, ACTUATORDESIRED_THRUST));
        
    fprintf(f, "UPDATE TIME = %f ms\n", uavtalk_get_float(msg, ACTUATORDESIRED_UPDATE_TIME));
    fprintf(f, "NUM LONG UPDATES = %f ms\n", uavtalk_get_float(msg, ACTUATORDESIRED_NUM_LONG_UPDATES));
}
void PrettyPrintAttitudeState(FILE *f, uavtalk_message_t *msg) {
    fprintf(f, "Pitch = %f, ", uavtalk_get_float(msg, ATTITUDESTATE_PITCH));
    fprintf(f, "Yaw = %f, ", uavtalk_get_float(msg, ATTITUDESTATE_YAW));
    fprintf(f, "Roll = %f\n", uavtalk_get_float(msg, ATTITUDESTATE_ROLL));
}
void PrettyPrintFlightStatus(FILE *f, uavtalk_message_t *msg) {
    fprintf(f, "Armed = %d, ", msg->data[FLIGHTSTATUS_ARMED]);
    fprintf(f, "Flight-Mode = %d\n", msg->data[FLIGHTSTATUS_FLIGHTMODE]);
}
void PrettyPrintGPSPositionSensor(FILE *f, uavtalk_message_t *msg) {
    fprintf(f, "[GPS POSITION SENSOR DATA]\n");
}
void PrettyPrintGPSTime(FILE *f, uavtalk_message_t *msg) {
    fprintf(f, "[GPS TIME DATA]\n");
}
void PrettyPrintGPSVelocitySensor(FILE *f, uavtalk_message_t *msg) {
    fprintf(f, "[GPS VELOCITY DATA]\n");
}
void PrettyPrintGyroState(FILE *f, uavtalk_message_t *msg) {
    fprintf(f, "XYZ = {%f %f %f} deg/s\n", 
        uavtalk_get_float(msg, GYROSTATE_X),
        uavtalk_get_float(msg, GYROSTATE_Y),
        uavtalk_get_float(msg, GYROSTATE_Z));
}
void PrettyPrintManualControlCommand(FILE *f, uavtalk_message_t *msg) {
    fprintf(f, "PITCH      = %d %%\n", uavtalk_get_float(msg, MANUALCONTROLCOMMAND_PITCH));
    fprintf(f, "YAW        = %d %%\n", uavtalk_get_float(msg, MANUALCONTROLCOMMAND_YAW));
    fprintf(f, "ROLL       = %d %%\n", uavtalk_get_float(msg, MANUALCONTROLCOMMAND_ROLL));
    fprintf(f, "THROTTLE   = %d %%\n", uavtalk_get_float(msg, MANUALCONTROLCOMMAND_THROTTLE));
    fprintf(f, "COLLECTIVE = %d %%\n", uavtalk_get_float(msg, MANUALCONTROLCOMMAND_COLLECTIVE));
    fprintf(f, "THRUST     = %d %%\n", uavtalk_get_float(msg, MANUALCONTROLCOMMAND_THRUST));
    
    fprintf(f, "CHANNELS:\n");
    for (int i = 0; i < 10; i++)
        fprintf(f, "    %02d: %d us\n", i, uavtalk_get_uint16(msg, MANUALCONTROLCOMMAND_CHANNEL0 + 2*i));
    
    fprintf(f, "CONNECTED: %s\n", msg->data[MANUALCONTROLCOMMAND_CONNECTED]?"YES":"NO");
    fprintf(f, "FLIGHT MODE SWITCH POSITION = %d\n", msg->data[MANUALCONTROLCOMMAND_FLIGHTMODESWITCHPOS]);
}
void PrettyPrintRateDesired(FILE *f, uavtalk_message_t *msg) {
    fprintf(f, "PYR = {%f %f %f} deg/s\n", 
        uavtalk_get_float(msg, RATEDESIRED_PITCH),
        uavtalk_get_float(msg, RATEDESIRED_YAW),
        uavtalk_get_float(msg, RATEDESIRED_ROLL));
        
    fprintf(f, "THRUST = %f %%\n", RATEDESIRED_THRUST);
}
void PrettyPrintReceiverStatus(FILE *f, uavtalk_message_t *msg) {
    fprintf(f, "%d %%\n", uavtalk_get_uint8(msg, RECEIVERSTATUS_QUALITY));
}
void PrettyPrintStabilizationBank(FILE *f, uavtalk_message_t *msg) {
    fprintf(f, "PITCH RATE pidl = {%f %f %f %f}\n",
        uavtalk_get_float(msg, STABILIZATIONBANK_PITCH_RATE_PID + 4*0),
        uavtalk_get_float(msg, STABILIZATIONBANK_PITCH_RATE_PID + 4*1),
        uavtalk_get_float(msg, STABILIZATIONBANK_PITCH_RATE_PID + 4*2),
        uavtalk_get_float(msg, STABILIZATIONBANK_PITCH_RATE_PID + 4*3));
        
    fprintf(f, "YAW RATE   pidl = {%f %f %f %f}\n",
        uavtalk_get_float(msg, STABILIZATIONBANK_YAW_RATE_PID + 4*0),
        uavtalk_get_float(msg, STABILIZATIONBANK_YAW_RATE_PID + 4*1),
        uavtalk_get_float(msg, STABILIZATIONBANK_YAW_RATE_PID + 4*2),
        uavtalk_get_float(msg, STABILIZATIONBANK_YAW_RATE_PID + 4*3));
        
    fprintf(f, "ROLL RATE  pidl = {%f %f %f %f}\n",
        uavtalk_get_float(msg, STABILIZATIONBANK_ROLL_RATE_PID + 4*0),
        uavtalk_get_float(msg, STABILIZATIONBANK_ROLL_RATE_PID + 4*1),
        uavtalk_get_float(msg, STABILIZATIONBANK_ROLL_RATE_PID + 4*2),
        uavtalk_get_float(msg, STABILIZATIONBANK_ROLL_RATE_PID + 4*3));
        
    fprintf(f, "PITCH pil = {%f %f %f}\n",
        uavtalk_get_float(msg, STABILIZATIONBANK_PITCH_PI + 4*0),
        uavtalk_get_float(msg, STABILIZATIONBANK_PITCH_PI + 4*1),
        uavtalk_get_float(msg, STABILIZATIONBANK_PITCH_PI + 4*2));
        
    fprintf(f, "YAW   pil = {%f %f %f}\n",
        uavtalk_get_float(msg, STABILIZATIONBANK_YAW_PI + 4*0),
        uavtalk_get_float(msg, STABILIZATIONBANK_YAW_PI + 4*1),
        uavtalk_get_float(msg, STABILIZATIONBANK_YAW_PI + 4*2));
        
    fprintf(f, "ROLL  pil = {%f %f %f}\n",
        uavtalk_get_float(msg, STABILIZATIONBANK_ROLL_PI + 4*0),
        uavtalk_get_float(msg, STABILIZATIONBANK_ROLL_PI + 4*1),
        uavtalk_get_float(msg, STABILIZATIONBANK_ROLL_PI + 4*2));
    
    fprintf(f, "MANUAL RATE  pyr = {%d %d %d} deg/sec\n",
        uavtalk_get_uint16(msg, STABILIZATIONBANK_MANUAL_RATE + 2*1),
        uavtalk_get_uint16(msg, STABILIZATIONBANK_MANUAL_RATE + 2*2),
        uavtalk_get_uint16(msg, STABILIZATIONBANK_MANUAL_RATE + 2*0));
    
    fprintf(f, "MAXIMUM RATE pyr = {%d %d %d} deg/sec\n",
        uavtalk_get_uint16(msg, STABILIZATIONBANK_MANUAL_RATE + 2*1),
        uavtalk_get_uint16(msg, STABILIZATIONBANK_MANUAL_RATE + 2*2),
        uavtalk_get_uint16(msg, STABILIZATIONBANK_MANUAL_RATE + 2*0));
        
    fprintf(f, "MAXIMUM pyr = {%d %d %d} deg\n",
        uavtalk_get_uint8(msg, STABILIZATIONBANK_PITCH_MAX),
        uavtalk_get_uint8(msg, STABILIZATIONBANK_YAW_MAX),
        uavtalk_get_uint8(msg, STABILIZATIONBANK_ROLL_MAX));
    
    fprintf(f, "STICK EXPO pyr = {%d %d %d} %%\n",
        uavtalk_get_uint8(msg, STABILIZATIONBANK_STICK_EXPO + 1),
        uavtalk_get_uint8(msg, STABILIZATIONBANK_STICK_EXPO + 2),
        uavtalk_get_uint8(msg, STABILIZATIONBANK_STICK_EXPO + 0));
    
    fprintf(f, "ACRO INSANITY FACTOR pyr = {%d %d %d} %%\n",
        uavtalk_get_uint8(msg, STABILIZATIONBANK_ACRO_INSANITY_FACTOR + 1),
        uavtalk_get_uint8(msg, STABILIZATIONBANK_ACRO_INSANITY_FACTOR + 2),
        uavtalk_get_uint8(msg, STABILIZATIONBANK_ACRO_INSANITY_FACTOR + 0));
    
    fprintf(f, "PIROUETTE COMPENSATION: %s\n", enStr[msg->data[STABILIZATIONBANK_ENABLE_PIRO_COMP]]);
    
    fprintf(f, "THRUST PID SCALING: %s\n", enStr[msg->data[STABILIZATIONBANK_EN_THRUST_PID_SCALE]]);
    
    fprintf(f, "THRUST PID SCALE CURVE:\n");
    fprintf(f, "      0%%: %3d\n", uavtalk_get_int8(msg, STABILIZATIONBANK_THRUST_PID_SCALE_CURVE + 0));
    fprintf(f, "     25%%: %3d\n", uavtalk_get_int8(msg, STABILIZATIONBANK_THRUST_PID_SCALE_CURVE + 1));
    fprintf(f, "     50%%: %3d\n", uavtalk_get_int8(msg, STABILIZATIONBANK_THRUST_PID_SCALE_CURVE + 2));
    fprintf(f, "     75%%: %3d\n", uavtalk_get_int8(msg, STABILIZATIONBANK_THRUST_PID_SCALE_CURVE + 3));
    fprintf(f, "    100%%: %3d\n", uavtalk_get_int8(msg, STABILIZATIONBANK_THRUST_PID_SCALE_CURVE + 4));
    
    const char* pidScaleSource[3] = {"Manual Control Throttle", "Stabilization Desired Thrust", "Actuator Desired Thrust"};
    const char* pidScaleTarget[7] = {"PID", "PI", "PD", "ID", "P", "I", "D"};
    const char* pidScaleAxes[7] = {"PYR", "PR", "YR", "R", "PY", "P", "Y"};
    
    fprintf(f, "THRUST PID SCALE:\n");
    fprintf(f, "    SOURCE = %s\n", pidScaleSource[msg->data[STABILIZATIONBANK_THRUST_PID_SCALE_SOURCE]]);
    fprintf(f, "    TARGET = %3s\n", pidScaleTarget[msg->data[STABILIZATIONBANK_THRUST_PID_SCALE_SOURCE]]);
    fprintf(f, "    AXES   = %3s\n", pidScaleAxes[msg->data[STABILIZATIONBANK_THRUST_PID_SCALE_SOURCE]]);
}
void PrettyPrintStabilizationDesired(FILE *f, uavtalk_message_t *msg) {
    fprintf(f, "PYR = {%f %f %f} deg\n", 
        uavtalk_get_float(msg, STABILIZATIONDESIRED_PITCH),
        uavtalk_get_float(msg, STABILIZATIONDESIRED_YAW),
        uavtalk_get_float(msg, STABILIZATIONDESIRED_ROLL));
        
    fprintf(f, "THRUST = %f %%\n", STABILIZATIONDESIRED_THRUST);
    
    const char* modeStr[4] = {"Roll", "Pitch", "Yaw", "Thrust"};
    
    fprintf(f, "MODE = %s\n", modeStr[msg->data[STABILIZATIONDESIRED_MODE]]);
}
void PrettyPrintStabilizationStatus(FILE *f, uavtalk_message_t *msg) {
    const char* olOpts[7] = {"Direct", "Direct With Limits", "Attitude", "Rattitude", "Weak Leveling", "Altitude", "Altitude Vario"};
    const char* ilOpts[6] = {"Direct", "Virtual Fly Bar", "Acro+", "Axis Lock", "Rate", "Cruise Control"};

    fprintf(f, "OUTER LOOP:\n");
    fprintf(f, "Pitch:  %s\n", olOpts[msg->data[STABILIZATIONSTATUS_OUTERLOOP_PITCH]]);
    fprintf(f, "Yaw:    %s\n", olOpts[msg->data[STABILIZATIONSTATUS_OUTERLOOP_YAW]]);
    fprintf(f, "Roll:   %s\n", olOpts[msg->data[STABILIZATIONSTATUS_OUTERLOOP_ROLL]]);
    fprintf(f, "Thrust: %s\n", olOpts[msg->data[STABILIZATIONSTATUS_OUTERLOOP_THRUST]]);
    fprintf(f, "INNER LOOP:\n");
    fprintf(f, "Pitch:  %s\n", ilOpts[msg->data[STABILIZATIONSTATUS_OUTERLOOP_PITCH]]);
    fprintf(f, "Yaw:    %s\n", ilOpts[msg->data[STABILIZATIONSTATUS_OUTERLOOP_YAW]]);
    fprintf(f, "Roll:   %s\n", ilOpts[msg->data[STABILIZATIONSTATUS_OUTERLOOP_ROLL]]);
    fprintf(f, "Thrust: %s\n", ilOpts[msg->data[STABILIZATIONSTATUS_OUTERLOOP_THRUST]]); 
}
void PrettyPrintSystemAlarms(FILE *f, uavtalk_message_t *msg) {
    const char* alarmOption[5] = {"Uninitialised", "OK", "Warning", "Critical", "Error"};

    fprintf(f, "SYSTEM CONFIGURATION = %s\n", alarmOption[msg->data[SYSTEMALARMS_ALARM_SYSTEMCONFIGURATION]]);
    fprintf(f, "BOOT FAULT           = %s\n", alarmOption[msg->data[SYSTEMALARMS_ALARM_BOOTFAULT]]);
    fprintf(f, "OUT OF MEMORY        = %s\n", alarmOption[msg->data[SYSTEMALARMS_ALARM_OUTOFMEMORY]]);    
    fprintf(f, "STACK OVERFLOW       = %s\n", alarmOption[msg->data[SYSTEMALARMS_ALARM_STACKOVERFLOW]]);
    fprintf(f, "CPU OVERLOAD         = %s\n", alarmOption[msg->data[SYSTEMALARMS_ALARM_CPUOVERLOAD]]);
    fprintf(f, "EVENT SYSTEM         = %s\n", alarmOption[msg->data[SYSTEMALARMS_ALARM_EVENTSYSTEM]]);
    fprintf(f, "TELEMETRY            = %s\n", alarmOption[msg->data[SYSTEMALARMS_ALARM_TELEMETRY]]);
    fprintf(f, "RECEIVER             = %s\n", alarmOption[msg->data[SYSTEMALARMS_ALARM_RECEIVER]]);
    fprintf(f, "MANUAL CONTROL       = %s\n", alarmOption[msg->data[SYSTEMALARMS_ALARM_MANUALCONTROL]]);
    fprintf(f, "ACTUATOR             = %s\n", alarmOption[msg->data[SYSTEMALARMS_ALARM_ACTUATOR]]);
    fprintf(f, "ATTITUDE             = %s\n", alarmOption[msg->data[SYSTEMALARMS_ALARM_ATTITUDE]]);
    fprintf(f, "SENSORS              = %s\n", alarmOption[msg->data[SYSTEMALARMS_ALARM_SENSORS]]);
    fprintf(f, "MAGNETOMETER         = %s\n", alarmOption[msg->data[SYSTEMALARMS_ALARM_MAGNETOMETER]]);
    fprintf(f, "AIRSPEED             = %s\n", alarmOption[msg->data[SYSTEMALARMS_ALARM_AIRSPEED]]);
    fprintf(f, "STABILIZATION        = %s\n", alarmOption[msg->data[SYSTEMALARMS_ALARM_STABILIZATION]]);
    fprintf(f, "GUIDANCE             = %s\n", alarmOption[msg->data[SYSTEMALARMS_ALARM_GUIDANCE]]);
    fprintf(f, "PATH PLAN            = %s\n", alarmOption[msg->data[SYSTEMALARMS_ALARM_PATHPLAN]]);
    fprintf(f, "BATTERY              = %s\n", alarmOption[msg->data[SYSTEMALARMS_ALARM_BATTERY]]);
    fprintf(f, "FLIGHT TIME          = %s\n", alarmOption[msg->data[SYSTEMALARMS_ALARM_FLIGHTTIME]]);
    fprintf(f, "I2C                  = %s\n", alarmOption[msg->data[SYSTEMALARMS_ALARM_I2C]]);
    fprintf(f, "GPS                  = %s\n", alarmOption[msg->data[SYSTEMALARMS_ALARM_GPS]]);
}
void PrettyPrintSystemStats(FILE *f, uavtalk_message_t *msg) {
    fprintf(f, "FLIGHT TIME                = %d ms\n", uavtalk_get_uint32(msg, SYSTEMSTATS_FLIGHTTIME));
    fprintf(f, "HEAP REMAINING             = %d bytes\n", uavtalk_get_uint32(msg, SYSTEMSTATS_HEAPREMAINING));
    fprintf(f, "IRQ STACK REMAINING        = %d bytes\n", uavtalk_get_uint16(msg, SYSTEMSTATS_IRQSTACKREMAINING));
    fprintf(f, "SYSTEM MOD STACK REMAINING = %d bytes\n", uavtalk_get_uint16(msg, SYSTEMSTATS_SYSMODSTACKREMAINING));
    fprintf(f, "CPU LOAD                   = %d %%\n", uavtalk_get_uint8(msg, SYSTEMSTATS_CPULOAD));
    fprintf(f, "CPU TEMP                   = %d C\n", uavtalk_get_int8(msg, SYSTEMSTATS_CPUTEMP));
    fprintf(f, "EVENT SYSTEM WARNING ID    = %d\n", uavtalk_get_uint32(msg, SYSTEMSTATS_EVENTSYSWARNINGID));
    fprintf(f, "OBJECT MANAGER CALLBACK ID = %d\n", uavtalk_get_uint32(msg, SYSTEMSTATS_OBJECTMGRCALLBACKID));
    fprintf(f, "OBJECT MANAGER QUEUE ID    = %d\n", uavtalk_get_uint32(msg, SYSTEMSTATS_OBJECTMGRQUEUEID));
    fprintf(f, "SYS SLOTS FREE             = %d slots\n", uavtalk_get_uint16(msg, SYSTEMSTATS_SYSSLOTSFREE));
    fprintf(f, "SYS SLOTS ACTIVE           = %d slots\n", uavtalk_get_uint16(msg, SYSTEMSTATS_SYSSLOTSACTIVE));
    fprintf(f, "USR SLOTS FREE             = %d slots\n", uavtalk_get_uint16(msg, SYSTEMSTATS_USRSLOTSFREE));
    fprintf(f, "USR SLOTS ACTIVE           = %d slots\n", uavtalk_get_uint16(msg, SYSTEMSTATS_USRSLOTSACTIVE));
}

void PrettyPrintMessageData(FILE *f, uavtalk_message_t *msg) {
	if (msg->length <= HEADER_LEN)
		return;

	switch(msg->objID) {
	case FLIGHTTELEMETRYSTATS_OBJID:
        PrettyPrintFlightTelemStats(f, msg);
        break;
	case GCSTELEMETRYSTATS_OBJID:
		PrettyPrintGCSTelemStats(f, msg);
		break;        
    case ACCELSTATE_OBJID:
        PrettyPrintAccelState(f, msg);
        break;
    case ACTUATORCOMMAND_OBJID:
        PrettyPrintActuatorCommand(f, msg);
        break;
    case ACTUATORDESIRED_OBJID:
        PrettyPrintActuatorDesired(f, msg);
        break;
    case ACCESSORYDESIRED_OBJID:
        PrettyPrintAccessoryDesired(f, msg);
        break;
	case ATTITUDESTATE_OBJID:
		PrettyPrintAttitudeState(f, msg);
		break;
	case FLIGHTSTATUS_OBJID:
		PrettyPrintFlightStatus(f, msg);
		break;
    case GYROSTATE_OBJID:
        PrettyPrintGyroState(f, msg);
        break;
	case GPSPOSITIONSENSOR_OBJID:
		PrettyPrintGPSPositionSensor(f, msg);
		break;
	case GPSTIME_OBJID:
		PrettyPrintGPSTime(f, msg);
		break;
	case GPSVELOCITYSENSOR_OBJID:
		PrettyPrintGPSVelocitySensor(f, msg);
		break;
    case MANUALCONTROLCOMMAND_OBJID:
		PrettyPrintManualControlCommand(f, msg);
		break;
    case RATEDESIRED_OBJID:
        PrettyPrintRateDesired(f, msg);
        break;
    case RECEIVERSTATUS_OBJID:
        PrettyPrintReceiverStatus(f, msg);
        break;
    case STABILIZATIONBANK_OBJID:
        PrettyPrintStabilizationBank(f, msg);
        break;
    case STABILIZATIONDESIRED_OBJID:
        PrettyPrintStabilizationDesired(f, msg);
        break;
    case STABILIZATIONSTATUS_OBJID:
        PrettyPrintStabilizationStatus(f, msg);
        break;
	case SYSTEMALARMS_OBJID:
        PrettyPrintSystemAlarms(f, msg);
        break;
    case SYSTEMSTATS_OBJID:
        PrettyPrintSystemStats(f, msg);
        break;
    default:
        fprintf(f, "Raw Data: [ ");
        for (int i = 0; i < msg->length - HEADER_LEN; i++)
            fprintf(f, "0x%02X ", msg->data[i]);
        fprintf(f, "]\n");
        break;
	}
    
    
}

void PrettyPrintMessage(FILE *f, uavtalk_message_t *msg)  {
	const char* delim = "\n";

	if (0) {
		// Print Timestamp
	}

	PrettyPrintMessageType(f, msg);
	fprintf(f, "%s", delim);

	fprintf(f, "Length = %d", msg->length);
	fprintf(f, "%s", delim);

	PrettyPrintObjectID(f, msg);	
	fprintf(f, "%s", delim);
    
    PrettyPrintInstanceID(f, msg);
    fprintf(f, "%s", delim);

	PrettyPrintMessageData(f, msg);
	fprintf(f, "%s", delim);

	fprintf(f, "\n");
}
