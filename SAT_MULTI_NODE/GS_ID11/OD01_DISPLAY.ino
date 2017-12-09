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

// Display data on OLED
void displayOLED(void) {
  if ((millis() - OD01_timeout) > 30000) {

    OD01.clear();
    OD01.println("Unit Name: ");              // 2 line
    OD01.println(XINABOX_DEVICENAME);


//    OD01.print("LOCAL RSSI: ");              // 1 Line
//    if (strcmp(loc_RSSI.c_str(), "NULL") != 0) {
//      OD01.print(loc_RSSI);
//      OD01.println(" dB");
//    } else {
//      OD01.println(" UNKNOWN");
//    }

    if (strcmp(sat_GPS_Time_MQTT, "NULL") != 0) {
      OD01.print(sat_GPS_Time_MQTT);
      OD01.println(" GMT");
    } else {
      OD01.println("NO GPS TIME");
    }

    OD01.print("SAT RSSI: ");                // 1 Line
    if (strcmp(sat_RSSI.c_str(), "NULL") != 0) {
      OD01.print(sat_RSSI);
      OD01.println(" dB");
    } else {
      OD01.println(" UNKNOWN");
    }

    if (strcmp(sat_hdop.c_str(), "NULL") != 0) {
      if ((atoi(sat_hdop.c_str()) < 5.0) && (atof(sat_hdop.c_str()) > 0)) {
        OD01.println("SAT Latitude:");             // 2 Lines
        OD01.println(sat_lattitude);
        OD01.println("SAT Longitude:");            // 2 Lines
        OD01.println(sat_longitude);
      } else {
        OD01.println("SAT Latitude:");             // 2 Lines
        OD01.println("UNKNOWN");
        OD01.println("SAT Longitude:");            // 2 Lines
        OD01.println("UNKNOWN");
      }
    } else {
      OD01.println("SAT Latitude:");             // 2 Lines
      OD01.println("UNKNOWN");
      OD01.println("SAT Longitude:");            // 2 Lines
      OD01.println("UNKNOWN");
    }
  }
}


