#ifndef UAVTALK_OBJECTS_H
#define UAVTALK_OBJECTS_H

// TELEMETRY OBJECTS:

// Flight Telemetry Stats
#define FLIGHTTELEMETRYSTATS_OBJID                  0x6737BB5A
#define FLIGHTTELEMETRYSTATS_TXDATARATE             0
#define FLIGHTTELEMETRYSTATS_TXBYTES                4
#define FLIGHTTELEMETRYSTATS_TXFAILURES             8
#define FLIGHTTELEMETRYSTATS_TXRETRIES              12
#define FLIGHTTELEMETRYSTATS_RXDATARATE             16
#define FLIGHTTELEMETRYSTATS_RXBYTES                20
#define FLIGHTTELEMETRYSTATS_RXFAILURES             24
#define FLIGHTTELEMETRYSTATS_RXSYNCERRORS           28
#define FLIGHTTELEMETRYSTATS_RXCRCERRORS            32
#define FLIGHTTELEMETRYSTATS_STATUS                 36
#define FLIGHTTELEMETRYSTAT_LEN                     37
#define FLIGHTTELEMETRYSTATS_CONNECT_TIMEOUT        10000

// Ground Control System Telemetry Stats
#define GCSTELEMETRYSTATS_OBJID                     0xCAD1DC0A
#define GCSTELEMETRYSTATS_TXDATARATE                0
#define GCSTELEMETRYSTATS_TXBYTES                   4
#define GCSTELEMETRYSTATS_TXFAILURES                8
#define GCSTELEMETRYSTATS_TXRETRIES                 12
#define GCSTELEMETRYSTATS_RXDATARATE                16
#define GCSTELEMETRYSTATS_RXBYTES                   20
#define GCSTELEMETRYSTATS_RXFAILURES                24
#define GCSTELEMETRYSTATS_RXSYNCERRORS              28
#define GCSTELEMETRYSTATS_RXCRCERRORS               32
#define GCSTELEMETRYSTATS_STATUS                    36
#define GCSTELEMETRYSTATS_LEN                       37
#define GCSTELEMETRYSTATS_SEND_PERIOD               5000


// ACTIVE OBJECTS:

// Accel State
#define ACCELSTATE_OBJID                            0xAD3C0E06
#define ACCELSTATE_X                                0
#define ACCELSTATE_Y                                4
#define ACCELSTATE_Z                                8

// Accessory Desired
#define ACCESSORYDESIRED_OBJID                      0xC409985A
#define ACCESSORYDESIRED_ACCESSORY                  0

// Actuator Command
#define ACTUATORCOMMAND_OBJID                       0xB8229FE4
#define ACTUATORCOMMAND_CHANNEL0                    0
#define ACTUATORCOMMAND_NUM_CHANNELS                12
#define ACTUATORCOMMAND_UPDATE_TIME                 24
#define ACTUATORCOMMAND_MAX_UPDATE_TIME             26
#define ACTUATORCOMMAND_NUM_FAILED_UPDATES          28

// Actuator Desired
#define ACTUATORDESIRED_OBJID                       0xEAE65C28
#define ACTUATORDESIRED_ROLL                        0
#define ACTUATORDESIRED_PITCH                       4
#define ACTUATORDESIRED_YAW                         8
#define ACTUATORDESIRED_THRUST                      12
#define ACTUATORDESIRED_UPDATE_TIME                 16
#define ACTUATORDESIRED_NUM_LONG_UPDATES            20

// Attitude Actual
#define ATTITUDESTATE_OBJID                         0xD7E0D964
#define ATTITUDESTATE_ROLL                          16
#define ATTITUDESTATE_PITCH                         20
#define ATTITUDESTATE_YAW                           24

// Flight Status
#define FLIGHTSTATUS_OBJID                          0xE33E5D4E
#define FLIGHTSTATUS_ARMED                          0
#define FLIGHTSTATUS_FLIGHTMODE                     1

// GPS Position
#define GPSPOSITIONSENSOR_OBJID                     0x98A7858C
#define GPSPOSITIONSENSOR_LAT                       0
#define GPSPOSITIONSENSOR_LON                       4
#define GPSPOSITIONSENSOR_ALTITUDE                  8
#define GPSPOSITIONSENSOR_GEOIDSEPARATION           12
#define GPSPOSITIONSENSOR_HEADING                   16
#define GPSPOSITIONSENSOR_GROUNDSPEED               20
#define GPSPOSITIONSENSOR_PDOP                      24
#define GPSPOSITIONSENSOR_HDOP                      28
#define GPSPOSITIONSENSOR_VDOP                      32
#define GPSPOSITIONSENSOR_STATUS                    36
#define GPSPOSITIONSENSOR_SATELLITES                37

// GPS Time
#define GPSTIME_OBJID                               0xD4478084
#define GPSTIME_YEAR                                0
#define GPSTIME_MONTH                               2
#define GPSTIME_DAY                                 3
#define GPSTIME_HOUR                                4
#define GPSTIME_MINUTE                              5
#define GPSTIME_SECOND                              6

// GPS Velocity
#define GPSVELOCITYSENSOR_OBJID                     0x0BC57454
#define GPSVELOCITYSENSOR_NORTH                     0
#define GPSVELOCITYSENSOR_EAST                      4
#define GPSVELOCITYSENSOR_DOWN                      8

// Gyroscope state
#define GYROSTATE_OBJID                             0x8C2D810A
#define GYROSTATE_X                                 0
#define GYROSTATE_Y                                 4
#define GYROSTATE_Z                                 8

// Manual Control Command
#define MANUALCONTROLCOMMAND_OBJID                  0xC4107480
#define MANUALCONTROLCOMMAND_THROTTLE               0
#define MANUALCONTROLCOMMAND_ROLL                   4
#define MANUALCONTROLCOMMAND_PITCH                  8
#define MANUALCONTROLCOMMAND_YAW                    12
#define MANUALCONTROLCOMMAND_COLLECTIVE             16
#define MANUALCONTROLCOMMAND_THRUST                 20
#define MANUALCONTROLCOMMAND_CHANNEL0               24
#define MANUALCONTROLCOMMAND_CHANNEL1               26
#define MANUALCONTROLCOMMAND_CHANNEL2               28
#define MANUALCONTROLCOMMAND_CHANNEL3               30
#define MANUALCONTROLCOMMAND_CHANNEL4               32
#define MANUALCONTROLCOMMAND_CHANNEL5               34
#define MANUALCONTROLCOMMAND_CHANNEL6               36
#define MANUALCONTROLCOMMAND_CHANNEL7               38
#define MANUALCONTROLCOMMAND_CHANNEL8               40
#define MANUALCONTROLCOMMAND_CHANNEL9               42
#define MANUALCONTROLCOMMAND_CONNECTED              43
#define MANUALCONTROLCOMMAND_FLIGHTMODESWITCHPOS    44

// Rate Desired
#define RATEDESIRED_OBJID                           0x3642723E
#define RATEDESIRED_ROLL                            0
#define RATEDESIRED_PITCH                           4
#define RATEDESIRED_YAW                             8
#define RATEDESIRED_THRUST                          12

// Receiver Status
#define RECEIVERSTATUS_OBJID                        0xFD24EDF2
#define RECEIVERSTATUS_QUALITY                      0

// Stabilization Bank
#define STABILIZATIONBANK_OBJID                     0x7FE7E2EE
#define STABILIZATIONBANK_ROLL_RATE_PID             0
#define STABILIZATIONBANK_PITCH_RATE_PID            16
#define STABILIZATIONBANK_YAW_RATE_PID              32
#define STABILIZATIONBANK_ROLL_PI                   48
#define STABILIZATIONBANK_PITCH_PI                  60
#define STABILIZATIONBANK_YAW_PI                    72
#define STABILIZATIONBANK_MANUAL_RATE               84
#define STABILIZATIONBANK_MAXIMUM_RATE              90
#define STABILIZATIONBANK_ROLL_MAX                  96
#define STABILIZATIONBANK_PITCH_MAX                 97
#define STABILIZATIONBANK_YAW_MAX                   98
#define STABILIZATIONBANK_STICK_EXPO                99
#define STABILIZATIONBANK_ACRO_INSANITY_FACTOR      102
#define STABILIZATIONBANK_ENABLE_PIRO_COMP          105
#define STABILIZATIONBANK_EN_THRUST_PID_SCALE       106
#define STABILIZATIONBANK_THRUST_PID_SCALE_CURVE    107
#define STABILIZATIONBANK_THRUST_PID_SCALE_SOURCE   112
#define STABILIZATIONBANK_THRUST_PID_SCALE_TARGET   113
#define STABILIZATIONBANK_THRUST_PID_SCALE_AXES     114

// Stabilization Desired
#define STABILIZATIONDESIRED_OBJID                  0xD8B6C8E2
#define STABILIZATIONDESIRED_ROLL                   0
#define STABILIZATIONDESIRED_PITCH                  4
#define STABILIZATIONDESIRED_YAW                    8
#define STABILIZATIONDESIRED_THRUST                 12
#define STABILIZATIONDESIRED_MODE                   16

// Stabilization Status
#define STABILIZATIONSTATUS_OBJID                   0xDB3FFA86
#define STABILIZATIONSTATUS_OUTERLOOP_ROLL          0
#define STABILIZATIONSTATUS_OUTERLOOP_PITCH         1
#define STABILIZATIONSTATUS_OUTERLOOP_YAW           2
#define STABILIZATIONSTATUS_OUTERLOOP_THRUST        3
#define STABILIZATIONSTATUS_INNERLOOP_ROLL          4
#define STABILIZATIONSTATUS_INNERLOOP_PITCH         5
#define STABILIZATIONSTATUS_INNERLOOP_YAW           6
#define STABILIZATIONSTATUS_INNERLOOP_THRUST        7

// System Alarms
#define SYSTEMALARMS_OBJID                          0x6B7639EC
#define SYSTEMALARMS_ALARM_SYSTEMCONFIGURATION      0
#define SYSTEMALARMS_ALARM_BOOTFAULT                1
#define SYSTEMALARMS_ALARM_OUTOFMEMORY              2
#define SYSTEMALARMS_ALARM_STACKOVERFLOW            3
#define SYSTEMALARMS_ALARM_CPUOVERLOAD              4
#define SYSTEMALARMS_ALARM_EVENTSYSTEM              5
#define SYSTEMALARMS_ALARM_TELEMETRY                6
#define SYSTEMALARMS_ALARM_RECEIVER                 7
#define SYSTEMALARMS_ALARM_MANUALCONTROL            8
#define SYSTEMALARMS_ALARM_ACTUATOR                 9
#define SYSTEMALARMS_ALARM_ATTITUDE                 10
#define SYSTEMALARMS_ALARM_SENSORS                  11
#define SYSTEMALARMS_ALARM_MAGNETOMETER             12
#define SYSTEMALARMS_ALARM_AIRSPEED                 13
#define SYSTEMALARMS_ALARM_STABILIZATION            14
#define SYSTEMALARMS_ALARM_GUIDANCE                 15
#define SYSTEMALARMS_ALARM_PATHPLAN                 16
#define SYSTEMALARMS_ALARM_BATTERY                  17
#define SYSTEMALARMS_ALARM_FLIGHTTIME               18
#define SYSTEMALARMS_ALARM_I2C                      19
#define SYSTEMALARMS_ALARM_GPS                      20

// System Stats
#define SYSTEMSTATS_OBJID                           0x40BFFEFC
#define SYSTEMSTATS_FLIGHTTIME                      0
#define SYSTEMSTATS_HEAPREMAINING                   4
#define SYSTEMSTATS_IRQSTACKREMAINING               8
#define SYSTEMSTATS_SYSMODSTACKREMAINING            10
#define SYSTEMSTATS_CPULOAD                         12
#define SYSTEMSTATS_CPUTEMP                         13
#define SYSTEMSTATS_EVENTSYSWARNINGID               14
#define SYSTEMSTATS_OBJECTMGRCALLBACKID             18
#define SYSTEMSTATS_OBJECTMGRQUEUEID                22
#define SYSTEMSTATS_SYSSLOTSFREE                    26
#define SYSTEMSTATS_SYSSLOTSACTIVE                  28
#define SYSTEMSTATS_USRSLOTSFREE                    30
#define SYSTEMSTATS_USRSLOTSACTIVE                  32


// OTHER OBJECTS:
#define ACCELGYROSETTINGS_OBJID                     0x1262B2D0
#define ACTUATORSETTINGS_OBJID                      0xD2AD60A2
#define ATTITUDESETTINGS_OBJID                      0x448954B8
#define FIRMWAREIAPOBJ_OBJID                        0x8328F252
#define FLIGHTMODESETTINGS_OBJID                    0xCC579770
#define HWSETTINGS_OBJID                            0xD4DB6008
#define MANUALCONTROLSETTINGS_OBJID                 0x72A1176C
#define MIXERSETTINGS_OBJID                         0x810D3A5E
#define MPUGYROACCELSETTINGS_OBJID                  0x7E2826C8
#define OBJECTPERSISTENCE_OBJID                     0x99C63292
#define RECEIVERACTIVITY_OBJID                      0xEF397852
#define STABILIZATIONSETTINGS_OBJID                 0x73603180
#define STABILIZATIONSETTINGSBANK1_OBJID            0xF03FDBA2
#define STABILIZATIONSETTINGSBANK2_OBJID            0x2B10CA1C
#define STABILIZATIONSETTINGSBANK3_OBJID            0xA86BDC0A
#define SYSTEMSETTINGS_OBJID                        0xD9D093B8

#endif