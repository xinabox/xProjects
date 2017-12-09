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
  Function to print Debug MSGS
  @param MSG, input string to print
 ***/
void DEBUG_PRINT(String DEBUG, boolean newline) {
  if (PRINT_EN == true) {
    Serial.begin(115200);
    PRINT_EN = false;
  }
  if ( PRINT_DEBUG == true ) {
    if (newline) {
      Serial.println(DEBUG);
    } else {
      Serial.print(DEBUG);
    }
  }
}
