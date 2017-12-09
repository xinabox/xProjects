/*****************************************************************************
    This is an example for the xCHIP DEMO KIT

    This examples read data from a SW01 and SL01 as primary sensors
    In Balloon Mission Activities its reads data from SN01 and SI01 Additionally

    Currently Supported on the following ☒CHIPs:
    - CW01

    You can buy these devices on our store!
    -----> https://xinabox.cc/CW01/
    -----> https://xinabox.cc/SW01/
    -----> https://xinabox.cc/SL01/
    -----> https://xinabox.cc/SI01/
    -----> https://xinabox.cc/SN01/

    The sensors communicates over the I2C Bus.
*****************************************************************************/
#ifndef xERROR_h
#define xERROR_h
/**************************** ERROR DEFINES *********************************/
// Main Check
boolean ERROR_OCCURED = false;

// Sensor Errors
boolean SW01_MISSING = false;
boolean SL01_MISSING = false;
boolean SI01_MISSING = false;
boolean SN01_MISSING = false;

// Captive Portal Error
boolean CAPTIVE_INDEX = false;
boolean CAPTIVE_LONG  = false;
boolean CAPTIVE_LAT   = false;
boolean CAPTIVE_ALT   = false;

// Blynk Error
boolean BLYNK_CONN_E  = false;
boolean BLYNK_AUTH_E  = false;

// MQTT Error
boolean MQTT_CONN_E   = false;
boolean MQTT_PUB_E    = false;

/**************************** ERROR CODES *********************************/
#define SW01_E  "E100"
#define SL01_E  "E101"
#define SI01_E  "E102"
#define SN01_E  "E103"

#define BLTNK_E_CONN  "E200"
#define BLYNK_E_AUTH  "E201"

#define MQTT_E_CONN   "E300"
#define MQTT_E_PUBB   "E301"

#define CAP_E_INDEX   "E400"
#define CAP_E_LONG    "E401"
#define CAP_E_LAT     "E402"
#define CAP_E_ALT     "E403"

#endif
