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

// PINGS a entered I2C address on the BUS
bool pingADDRESS(uint8_t _address) {
  // Set flag status
  bool status = false;
  // Check the flag status to check if OD01 is connected and ping was succesful
  for (byte i = 0; i < 10; i++) {
    Wire.beginTransmission(_address);
    if (Wire.endTransmission () == 0) { // Device is connected and ping successful
      status = true; // set flag
      break; // exit loop
    }else if (i == 9) { // Device not found cannot ping device address
      status = false; // set flag
      break; // exit loop
    }
    delay(1);
  }
  return status;
}


