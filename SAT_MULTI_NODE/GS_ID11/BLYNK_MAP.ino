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

void task_BlynkMap(void){
  if ((atof(sat_hdop.c_str()) < 5.0) && (strcmp(sat_hdop.c_str(), "NULL") != 0)&& (atof(sat_hdop.c_str()) > 0)){
    if ((strcmp(sat_lattitude.c_str(), "NULL") != 0) && (strcmp(sat_longitude.c_str(), "NULL") != 0)){
      myMap.clear();
      Blynk.virtualWrite(V7, 1, sat_lattitude, sat_longitude, "Satellite"); //These values must be floats.
    }
  }
}
