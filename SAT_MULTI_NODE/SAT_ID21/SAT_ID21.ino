/******************************************************************************
    This is an example the RL01 to act as a state machine

    You can buy one on our store!
    -----> https://xinabox.cc/products/CW01/

    Currently Supported on the following ☒CHIP:
    - RL01/RL02/RL01
    - CW01
    - PB04
    - SW01
    - SL01
    - OC01
    - SN01
    - SI01

    The sensor communicates over the I2C Bus.

******************************************************************************/

// Setup for CW01 Low Power
#define FREQUENCY    80                  // valid 80, 160

#include "ESP8266WiFi.h"
extern "C" {
#include "user_interface.h"
}

/**************************** Library Includes *******************************/
//XINABOX
#include <xCore.h>
#include <xSW01.h>
#include <xSL01.h>
#include <xSI01.h>
#include <xSN01.h>
#include <xRL0X.h>
#include "xVARIABLES.h"

/*************************** SYSTEM VARIABLES ********************************/
// Radio Defines
#define RL01_FREQ 433.0
#define RL02_FREQ 868.0
#define RL03_FREQ 915.0

// Radio ID
#define ADDR_ID 0x21
#define FROM_ID 0x21
#define TO_ID   0x11

/***************************** Sketch Code ***********************************/

void setup() {
  PRINT_DEBUG = PRINT_EN = true;
  // Set RGB pin directions
  pinMode(CW01_RED, OUTPUT);
  pinMode(CW01_GREEN, OUTPUT);
  pinMode(CW01_BLUE, OUTPUT);

  WiFi.forceSleepBegin();                  // turn off ESP8266 RF
  delay(10);                               // give RF section time to shutdown
  system_update_cpu_freq(FREQUENCY);
  
  // Start I2C bus
  Wire.pins(2, 14);
  Wire.begin();
  Wire.setClockStretchLimit(15000);

  satTimeout = millis();

  digitalWrite(CW01_RED, HIGH);
}

void loop() {
  STATE_MACHINE();
}

