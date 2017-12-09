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

// tell radio to be a slave
void I_AM_MASTER(uint8_t SLAVE_CMD) {
  if (pingADDRESS(r.RL03_ID)) {
    Serial.println("*WM: Found RL01");
    RL0X_HERE = true;
    startRL0X(RL01_FREQ);
    DEBUG_RGB(CW01_GREEN, 100);
  } else {
    Serial.println("*WM: Radio not Found");
    DEBUG_RGB(CW01_RED, 100);
    CR0X_HERE = false;
    RL0X_HERE = false;
  }
}






