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

void BLYNK_LOOP(void) {
  if (millis() > (tick_Blynk + 1)) {
    runBlynk();
    tick_Blynk = millis();
  }

  if (millis() > (tick_Update + 5000)) { //Highest Priority
    task_BlynkUpdate();
    tick_Update = millis();
  }

  if (millis() > (tick_BlynkMap + 10000)) {
    task_BlynkMap();
    tick_BlynkMap = millis();
  }
}
