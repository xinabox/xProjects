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

void DEBUG_RGB(int led, int blink_time) {
  digitalWrite(led, HIGH);
  delay(blink_time);
  digitalWrite(led, LOW);
  delay(blink_time);
  digitalWrite(led, HIGH);
  delay(blink_time);
  digitalWrite(led, LOW);
  delay(blink_time);
}

void DEBUG_OD01(void){
  
}

