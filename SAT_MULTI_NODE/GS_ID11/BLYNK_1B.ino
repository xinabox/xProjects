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


void BLYNK_PHASE2(void)
{
  memset(sat_GPS_temp, '\0', sizeof(sat_GPS_temp));
  memset(sat_GPS_Blynk, '\0', sizeof(sat_GPS_Blynk));

  strcpy(sat_GPS_temp, sat_date.c_str());
  if (strcmp(sat_GPS_temp, "NULL") != 0) {
    if (sat_GPS_temp[1] == 0x00) {
      sprintf(sat_GPS_Blynk, "00/00/0000");
    } else if (sat_GPS_temp[5] == 0x00) {
      sprintf(sat_GPS_Blynk, "0%c/%c%c/20%c%c", sat_GPS_temp[0], sat_GPS_temp[1], sat_GPS_temp[2], sat_GPS_temp[3], sat_GPS_temp[4]);
    } else {
      sprintf(sat_GPS_Blynk, "%c%c/%c%c/20%c%c", sat_GPS_temp[0], sat_GPS_temp[1], sat_GPS_temp[2], sat_GPS_temp[3], sat_GPS_temp[4], sat_GPS_temp[5]);
    }
    Blynk.virtualWrite(V9, sat_GPS_Blynk);
  }


  memset(sat_GPS_temp, '\0', sizeof(sat_GPS_temp));
  memset(sat_GPS_Blynk, '\0', sizeof(sat_GPS_Blynk));

  strcpy(sat_GPS_temp, sat_time.c_str());

  if (strcmp(sat_GPS_temp, "NULL") != 0) {
    if (sat_GPS_temp[1] == 0x00) {
      sprintf(sat_GPS_Blynk, "00:00:00");
    } else if (sat_GPS_temp[5] == 0x00) {
      sprintf(sat_GPS_Blynk, "0%c:%c%c:%c%c", sat_GPS_temp[0], sat_GPS_temp[1], sat_GPS_temp[2], sat_GPS_temp[3], sat_GPS_temp[4]);
    } else {
      sprintf(sat_GPS_Blynk, "%c%c:%c%c:%c%c", sat_GPS_temp[0], sat_GPS_temp[1], sat_GPS_temp[2], sat_GPS_temp[3], sat_GPS_temp[4], sat_GPS_temp[5]);
    }
    Blynk.virtualWrite(V8, sat_GPS_Blynk);
  }

  if (strcmp(sat_lattitude.c_str(), "NULL") != 0) {
    Blynk.virtualWrite(V4, sat_lattitude);
  }

  if (strcmp(sat_longitude.c_str(), "NULL") != 0) {
    Blynk.virtualWrite(V5, sat_longitude);
  }

  if (strcmp(sat_altitude.c_str(), "NULL") != 0) {
    Blynk.virtualWrite(V6, sat_altitude);
  }

  if ((strcmp(sat_ascendrate.c_str(), "NULL") != 0) && (strcmp(sat_ascendrate.c_str(), "NAN") != 0)) {
    Blynk.virtualWrite(V14, sat_ascendrate);
  } else if (strcmp(sat_ascendrate.c_str(), "NAN") == 0) {
    Blynk.virtualWrite(V14, "0.0");
  }

  if (strcmp(loc_RSSI.c_str(), "NULL") != 0) {
    Blynk.virtualWrite(V11, loc_RSSI);
  }

  if (strcmp(sat_RSSI.c_str(), "NULL") != 0) {
    Blynk.virtualWrite(V10, sat_RSSI);
  }

  if (strcmp(sat_BatVoltage.c_str(), "NULL") != 0) {
    Blynk.virtualWrite(V15, sat_BatVoltage);
  }

  if (strcmp(sat_NumSats.c_str(), "NULL") != 0) {
    Blynk.virtualWrite(V13, sat_NumSats);
  }

  if (strcmp(sat_sog.c_str(), "NULL") != 0) {
    Blynk.virtualWrite(V12, sat_sog);
  }

  if (strcmp(sat_cog.c_str(), "NULL") != 0) {
    Blynk.virtualWrite(V16, sat_cog);
  }
}
