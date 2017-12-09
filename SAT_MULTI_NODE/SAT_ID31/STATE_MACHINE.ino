/******************************************************************************
    This is an example the RL01 to act as a state machine

    You can buy one on our store!
    -----> https://xinabox.cc/products/CW01/
    -----> https://xinabox.cc/products/RL01/   

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

/***
   Blocking function to keep Module in either
   GS Mode or SAT mode
 ***/
void STATE_MACHINE(void) {
  if ((millis() - satTimeout) > 20000) {
    SAT = true;
    digitalWrite(CW01_RED, LOW);
  }
  if (SAT == true) {
    PRINT_DEBUG = PRINT_EN = true;
    satRADIO();
    sensorSETUP();
    digitalWrite(CW01_RED, LOW);
    DEBUG_PRINT(String("CONFIG:SAT"), true);
    SN01.poll();
    while ((SN01.getHDOP() > 5.0)) {
      SN01.poll();
      delay(100);
    }
    digitalWrite(CW01_GREEN, HIGH);         
    while (1) {
      SAT_LOOP();
    }
  }
}

/***
  Function to set the Radio send/recieve headers
  @param ID_TO, the header to be sent in all subsequent messages
  @param ID_FROM, the header to be sent in all subsequent messages
  @param APP_ID, Sets and clears bits in the FLAGS header to be sent in all subsequent messages
 ***/
void SET_RADIO_HEADERS(uint8_t ID_RADIO, uint8_t ID_FROM, uint8_t ID_TO) {
  RL0X.setThisAddress(ID_RADIO);
  RL0X.setHeaderFrom(ID_FROM);
  RL0X.setHeaderTo(ID_TO);
}

