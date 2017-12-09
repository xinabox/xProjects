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

// Get timestamp
void getTimeStamp(void) {
  dateTime = NTPch.getNTPtime(0.0, 0);

  if (dateTime.valid) {
    timeStamp = dateTime.year;
    timeStamp += "-";
    if (dateTime.month < 10) {
      timeStamp += "0";
      timeStamp += dateTime.month;
      timeStamp += "-";
    } else {
      timeStamp += dateTime.month;
      timeStamp += "-";
    }
    if (dateTime.day < 10) {
      timeStamp += "0";
      timeStamp += dateTime.day;
    } else {
      timeStamp += dateTime.day;
    }
    timeStamp += "T";
    if (dateTime.hour < 10) {
      timeStamp += "0";
      timeStamp += dateTime.hour;
      timeStamp += ":";
    } else {
      timeStamp += dateTime.hour;
      timeStamp += ":";
    }
    if (dateTime.minute < 10) {
      timeStamp += "0";
      timeStamp += dateTime.minute;
      timeStamp += ":";
    } else {
      timeStamp += dateTime.minute;
      timeStamp += ":";
    }
    if (dateTime.second < 10) {
      timeStamp += "0";
      timeStamp += dateTime.second;
    } else {
      timeStamp += dateTime.second;
    }
  }
}
