/******************************************************************************
    This is an example the RL01 to act as a state machine

    You can buy one on our store!
    -----> https://xinabox.cc/RL01/

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
 * Initialize the Sensors
 ***/
void sensorSETUP(void) {
  SW01.begin();
  SL01.begin();
  SI01.begin();
  SN01.begin();
}

/***
 * Poll the Sensors
 ***/
void sensorPOLL(void) {
  SW01.poll();
  SL01.poll();
  SI01.poll();
}

