/*****************************************************************************
    This is an example for the xCHIP DEMO KIT

    This examples read data from a SW01 and SL01 as primary sensors
    In Balloon Mission Activities its reads data from SN01 and SI01 Additionally

    Currently Supported on the following ☒CHIPs:
    - CW01

    You can buy these devices on our store!
    -----> https://xinabox.cc/products/CW01/
    -----> https://xinabox.cc/products/SW01/
    -----> https://xinabox.cc/products/SL01/
    -----> https://xinabox.cc/products/SI01/
    -----> https://xinabox.cc/products/SN01/

    The sensors communicates over the I2C Bus.
*****************************************************************************/

#ifndef xDEMO_h
#define xDEMO_h

/**************************** SYSTEM DEFINES *********************************/
#define PUBLISH_INTERVAL  30000
#define SERVER_CHECK_INTERVAL  3000

boolean isBOOT = false;
uint8_t tick_WiFi = 0;

String tempPayload = "";
/************************* XINABOX MQTT Setup *********************************/
String    XINABOX_SERVER      =  "mqtt.xinabox.cc";
uint16_t  XINABOX_SERVERPORT_1  =  80;
uint16_t  XINABOX_SERVERPORT_2  =  1883;

String    XINABOX_USERNAME    = "admin";
String    XINABOX_PASSWORD    = "JT3PhtAwjJsxrV7N";

unsigned long lastSend;
unsigned long lastServerCheck;
unsigned long satSendInterval;
unsigned long lastError;
unsigned long lastUploadHistorical;

/************************** XINABOX Blynk Setup *****************************/
String    XINABOX_BLYNK      =  "link.xinabox.cc";
uint16_t  XINABOX_BLYNKPORT_1  =  8442;
uint16_t  XINABOX_BLYNKPORT_2  =  80;
char      XINABOX_BLYNK_AUTH[40];
boolean   USE_BLYNK = false;

uint8_t tick_BLYNK = 0;
boolean LogAvailable = false;
/***************************** JSON Data ************************************/
// variable to store unique client name based on chip ID
String CLIENT_ID;
String CLIENT_MAC;
String timeStamp;

char ServerClientID[40];
char topic_GS[40];
char topic_SAT[40];
char temp_index[20];

//define your default values here, if there are different values in config.json, they are overwritten.
char XINABOX_SOFTWARE_REV[10];
char XINABOX_DEVICENAME[20];
char XINABOX_LATITUDE[15];
char XINABOX_LONGITUDE[15];
char XINABOX_IN_OUT[1];
char XINABOX_ALTITUDE[15];
char XINABOX_HOSTNAME[15];
char XINABOX_INDEX[20];
char XINABOX_ORGANIZATION[20];

//flag for saving data
bool shouldSaveConfig = true;

/*************************** Balloon Mission Code *****************************/
// Radio ID
#define RADIO_ID 0x25

#endif
