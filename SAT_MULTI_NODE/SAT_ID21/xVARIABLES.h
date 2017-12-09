/******************************************************************************
    This is an example the RL01 Satelitte Transciever

    You can buy one on our store!
    -----> https://xinabox.cc/producrs/RL01/

    Currently Supported on the following ☒CHIP:
    - RL01/RL02/RL01
    - CW01
    - SW01
    - SL01
    - OC01
    - SN01
    - SI01

    The sensor communicates over the I2C Bus.

******************************************************************************/

#ifndef xVARIABLES_h
#define xVARIABLES_h

#define ACK 0xFF
/*************************** SYSTEM VARIABLES ********************************/
// Radio Variables
uint8_t recvCMD = 0;          // recieved command

boolean sendDATA = false;
int receivedRSSI = 0;
uint8_t len = 0;
uint8_t I2C_BUF[5];
uint8_t bufidx = 0;

// Station Define
boolean SAT = false;
boolean GS = false;
long satTimeout = 0;
uint8_t GS_bytesAvailable = 0;

// Satelite Defines
float ascendRate = 0;
float oldAlt = 0;
float newAlt = 0;
long newTime = 0;
long oldTime = 0;

long tick_readSensor = 0;
long tick_pollSensor = 0;
long tick_Recieve = 0;
long tick_SN01 = 0;

// Serial DEBUG Print enable
boolean PRINT_DEBUG; 
boolean PRINT_EN;
boolean INCOMING_PARSE = false;

/****************************** Data Buffers *********************************/
char satBuffer[32];
char append[8];

#endif

