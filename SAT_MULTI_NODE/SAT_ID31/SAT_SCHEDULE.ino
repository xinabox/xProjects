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
   Task Schedulers
 ***/
void satSCHEDULER(void) {
  if (millis() > (tick_SN01 + 1)) {
    SN01.poll();
    tick_SN01 = millis();
  }
  if ( millis() > (tick_Recieve + 100)) {
    satReceive();
    tick_Recieve = millis();
    wdt_reset();
  }
  if ( millis() > (tick_pollSensor + 100)) {
    sensorPOLL();
    tick_pollSensor = millis();
  }
}

