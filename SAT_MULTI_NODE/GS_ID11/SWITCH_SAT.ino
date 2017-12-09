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

// Change Radio IDs
void setNewHeader(uint8_t ID) {
  RL0X.setHeaderTo(ID); // set new header for to address
  delay(50);
}

void getTOAST(uint8_t ID) {
  Serial.println("\nCollecting ToastSAT Data...");
  Serial.print("Radio ID : ");
  Serial.println("0x" + String(ID, HEX));
  setNewHeader(ID);

  satData(1); // SW01 data
  satData(2); // SI01 data
  satData(3); // SL01 data
  satData(4); // PB04 data
  satData(7); // GPS3 data incl - Altitude, SOG, COG, HDOP and Satelittes Conncted
  satData(5); // GPS1 data incl - Time and Date
  satData(6); // GPS2 data incl - Latitude and Longitude
  satData(8); // GPS4 data incl - Ascent Rate
  TOAST_SAT_PUBLISH();
}

