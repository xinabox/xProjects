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

void POLL_PHASE2(void) {
  if (pingADDRESS(0x76) == true) {
    SW01.poll();
  }
  if ((pingADDRESS(0x10) && pingADDRESS(0x29)) == true) {
    SL01.poll();
  }
  if ((pingADDRESS(0x1C) && pingADDRESS(0x6A)) == true) {
    SI01.poll();
  }
}


void START_PHASE2(void) {
  SW01.begin();
  SL01.begin();
  SN01.begin();
  SI01.begin();
}


