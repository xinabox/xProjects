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

#ifndef xBALLOON_h
#define xBALLOON_h

/***************************** Balloon Mission *******************************/
#define MASTER_ID 0x25
#define ACK 0xFF

/************************** Mission Critical DatA *****************************/
String sat_lattitude = "NULL";
String sat_longitude = "NULL";
String sat_altitude  = "NULL";
String sat_date  = "NULL";
String sat_time  = "NULL";
String sat_sog  = "NULL";
String sat_cog  = "NULL";
String sat_hdop  = "NULL";
String sat_RSSI = "NULL";
String sat_BatVoltage = "NULL";
String sat_NumSats = "NULL";
String loc_RSSI = "NULL";
String gForce = "NULL";
String sat_ascendrate = "NULL";

unsigned int loc_hdop = 999;
unsigned int loc_sog = 0;
unsigned int loc_cog = 0;
unsigned int loc_numsats = 0;
long loc_date = 0;
long loc_time = 0;
long loc_lattitude = 0;
long loc_longitude = 0;
long loc_altitude = 0;

String tempString = "";

uint8_t radio_retry = 0;
uint8_t max_radio_retries = 3;
uint8_t OC01_burn_time = 5;
uint8_t critical_data_count = 1;

int collectingData = 0;
int setupComplete = 0;
int Testcheck = 0;
long OD01_timeout = 0;
int receivedRSSI = 0;

/***************************** SYSTEM DEFINES *********************************/
boolean CR0X_HERE = false;
boolean RL0X_HERE = false;
byte SLAVE_ADDR = 0;

uint8_t len = 0;

uint8_t bail = 0;

/*************************** REGISTER STRUCTURES ******************************/
struct CONTROL_REG {
  byte STATE_REG   = 0x49;
  byte CMD_REG     = 0x50;
  byte BYTES_REG   = 0x51;
  byte READ_REG    = 0x52;
  byte RADIO_REG   = 0x53;
};

struct RADIO_REG {
  byte CR01_ID  = 0xFA;
  byte CR02_ID  = 0xFB;
  byte CR03_ID  = 0xFC;
  byte RL01_ID  = 0x2F;
  byte RL02_ID  = 0x2F;
  byte RL03_ID  = 0x2F;
};

struct SENSOR_REG {
  char  buffer[32];
  int16_t bufferidx;
  String SW01_T;
  String SW01_H;
  String SW01_P;
  String SW03_T;
  String SW03_P;
  String SL01_L;
  String SL01_A;
  String SL01_B;
  String SL01_I;
  String PB04_V;
  String PB04_C;
  String SI01_GF;
  String SI01_R;
  String SI01_P;
  String SI01_Y;
  String SN01_S;
  String SN01_STAT;
  String SN01_D;
  String SN01_T;
  String SN01_LAT;
  String SN01_LONG;
  String SN01_ALT;
  String SN01_SOG;
  String SN01_COG;
  String SN01_HDOP;
  String SN01_SAT;
  String SAT_RSSI;
  String LOC_RSSI;
  String OC01_R;
  uint8_t OC01_B;
  String CALC_AR;
  String SAT_STATUS;
};

/****************************** Blynk Parameters ****************************/

int V0_State = 0, V1_State = 0, V2_State = 0, V3_State = 0;
int BW_StateLatch = 0;

long tick_Update = 0,
     tick_BlynkMap = 0,
     tick_Map = 0,
     tick_BW_CMD = 0,
     tick_Blynk = 0,
     tick_criticalData = 0,
     tick_SN01 = 0,
     tick_OD01 = 0,
     tick_MQTT = 0;

/****************************** Data Buffers *********************************/
char sat_GPS_temp[30];
char sat_GPS_Date_temp[30];
char sat_GPS_Time_temp[30];
char sat_GPS_Date_MQTT[30];
char sat_GPS_Time_MQTT[30];
char loc_GPS_Date_temp[30];
char loc_GPS_Date_MQTT[30];
char loc_GPS_Time_temp[30];
char loc_GPS_Time_MQTT[30];
char sat_GPS_Blynk[30];
char sat_BURN_Status[4];
uint8_t satBuffer[32];
uint8_t I2C_BUF[5];

char topic_STEM[40];
char topic_COOKIE[40];
char topic_TOAST[40];

#endif
