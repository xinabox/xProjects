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

// publish satelitte data
void TOAST_SAT_PUBLISH(void) {
  uint8_t comma_check = 0;

  String sat_payload = "{";
  sat_payload += "\"GS\": {";

  // GET SW01 Data
  if (pingADDRESS(0x76) == true) {
    sat_payload += "\"SW01\": {";
    sat_payload += "\"Temperature(C)\":"; sat_payload += String(SW01.getTempC(), 1); sat_payload += ",";
    sat_payload += "\"Humidity(%)\":"; sat_payload += String(SW01.getHumidity(), 0); sat_payload += ",";
    sat_payload += "\"Pressure(Pa)\":"; sat_payload += String(SW01.getPressure(), 0);
    sat_payload += "}";
    comma_check = 1;
  }
  // GET SL01 Data
  if ((pingADDRESS(0x10) && pingADDRESS(0x29)) == true) {
    if (comma_check == 1) {
      sat_payload += ",";
    }
    sat_payload += "\"SL01\": {";
    sat_payload += "\"Lux\":"; sat_payload += String(SL01.getLUX(), 0);  sat_payload += ",";
    sat_payload += "\"UVA(mW/m^2)\":"; sat_payload += String(SL01.getUVA(), 0);  sat_payload += ",";
    sat_payload += "\"UVB(mW/m^2)\":"; sat_payload += String(SL01.getUVB(), 0);  sat_payload += ",";
    sat_payload += "\"UVI\":"; sat_payload += String(SL01.getUVIndex(), 1);
    sat_payload += "}";
    comma_check = 1;
  }

  // GET SI01 Data
  if ((pingADDRESS(0x1C) && pingADDRESS(0x6A)) == true) {
    if (comma_check == 1) {
      sat_payload += ",";
    }
    sat_payload += "\"SI01\": {";
    sat_payload += "\"GForce\":"; sat_payload += SI01.getGForce(); sat_payload += ",";
    sat_payload += "\"Roll(Deg)\":"; sat_payload += SI01.getRoll(); sat_payload += ",";
    sat_payload += "\"Pitch(Deg)\":"; sat_payload += SI01.getPitch(); //sat_payload += ",";
    //sat_payload += "\"Yaw(Deg)\":"; sat_payload += SI01.getYaw();
    sat_payload += "}";
    comma_check = 1;
  }

  // Get CW01 specific Data
  if (comma_check == 1) {
    sat_payload += ",";
  }
  comma_check = 0;
  sat_payload += "\"CW01\": {";
  sat_payload += "\"RSSI\":"; sat_payload += WiFi.RSSI();         sat_payload += ",";
  sat_payload += "\"Chip ID\":"; sat_payload += CLIENT_ID;         sat_payload += ",";
  sat_payload += "\"MAC\":\""; sat_payload += WiFi.macAddress();  sat_payload += "\"";
  sat_payload += "},";

  // insert user specific data
  sat_payload += "\"Input\": {";
  if (strlen(XINABOX_DEVICENAME) != 0) {
    sat_payload += "\"Unit Name\":\"";
    sat_payload += "TOAST_SAT";
    sat_payload += "\"";
  }
  if (strlen(XINABOX_ORGANIZATION) != 0) {
    sat_payload += ",";
    sat_payload += "\"Organization\":";   sat_payload += "\"";
    sat_payload += XINABOX_ORGANIZATION;  sat_payload += "\"";
  }
  if (strlen(XINABOX_LONGITUDE) != 0 && strlen(XINABOX_LATITUDE) != 0) {
    sat_payload += ",";
    sat_payload += "\"Location\":["; sat_payload += XINABOX_LATITUDE; sat_payload += ","; sat_payload += XINABOX_LONGITUDE; sat_payload += "]";
  }
  if (strlen(XINABOX_ALTITUDE) != 0) {
    sat_payload += ",";
    sat_payload += "\"Altitude(m)\":"; sat_payload += XINABOX_ALTITUDE;
  }
  if (strlen(XINABOX_IN_OUT) != 0) {
    sat_payload += ",";
    sat_payload += "\"Indoor\":";   sat_payload += XINABOX_IN_OUT;
  }
  sat_payload += "},";

  if (pingADDRESS(0x42) == true) {

    sat_payload += "\"SN01\": {";
    sat_payload += "\"HDOP\":"; sat_payload += String((int)SN01.getHDOP()); sat_payload += ",";
    sat_payload += "\"Number Satellites\":";   sat_payload += String(SN01.getSatelitesConnected(), DEC); sat_payload += ",";
    loc_hdop = (float)SN01.getHDOP();
    if ((loc_hdop < 5.0)) {
      sat_payload += "\"STATUS\":\"ONLINE\"";
      sat_payload += ",";
      loc_date = SN01.getDate();
      loc_time = SN01.getTime();

      if ((loc_date != 0) && (loc_time != 0)) {
        memset(loc_GPS_Date_temp, '\0', sizeof(loc_GPS_Date_temp));
        memset(loc_GPS_Date_MQTT, '\0', sizeof(loc_GPS_Date_MQTT));

        ltoa(loc_date, loc_GPS_Date_temp, 10);
        //strcpy(loc_GPS_Date_temp, tempString.c_str());

        if (loc_GPS_Date_temp[1] == 0x00) {
          // do nothing
        } else if (loc_GPS_Date_temp[5] == 0x00) {
          sprintf(loc_GPS_Date_MQTT, "20%c%c-%c%c-0%cT", loc_GPS_Date_temp[3], loc_GPS_Date_temp[4], loc_GPS_Date_temp[1], loc_GPS_Date_temp[2], loc_GPS_Date_temp[0]);
        } else {
          sprintf(loc_GPS_Date_MQTT, "20%c%c-%c%c-%c%cT", loc_GPS_Date_temp[4], loc_GPS_Date_temp[5], loc_GPS_Date_temp[2], loc_GPS_Date_temp[3], loc_GPS_Date_temp[0], loc_GPS_Date_temp[1]);
        }

        memset(loc_GPS_Time_temp, '\0', sizeof(loc_GPS_Time_temp));
        memset(loc_GPS_Time_MQTT, '\0', sizeof(loc_GPS_Time_MQTT));

        tempString = "";
        ltoa(loc_time, loc_GPS_Time_temp, 10);
        //strcpy(loc_GPS_Time_temp, tempString.c_str());

        if (loc_GPS_Time_temp[1] == 0x00) {
          // do nothing
        } else if (sat_GPS_Time_temp[6] == 0x00) {
          sprintf(sat_GPS_Time_MQTT, "00:%c%c:%c%c", sat_GPS_Time_temp[0], sat_GPS_Time_temp[1], sat_GPS_Time_temp[2], sat_GPS_Time_temp[3]);
        } else if (loc_GPS_Time_temp[7] == 0x00) {
          sprintf(loc_GPS_Time_MQTT, "0%c:%c%c:%c%c", loc_GPS_Time_temp[0], loc_GPS_Time_temp[1], loc_GPS_Time_temp[2], loc_GPS_Time_temp[3], loc_GPS_Time_temp[4]);
        } else {
          sprintf(loc_GPS_Time_MQTT, "%c%c:%c%c:%c%c", loc_GPS_Time_temp[0], loc_GPS_Time_temp[1], loc_GPS_Time_temp[2], loc_GPS_Time_temp[3], loc_GPS_Time_temp[4], loc_GPS_Time_temp[5]);
        }

        if ((loc_GPS_Date_temp[1] != 0x00) && (loc_GPS_Time_temp[1] != 0x00)) {
          sat_payload += "\"Timestamp\":{";
          sat_payload += "\"Created\":\"";
          sat_payload += loc_GPS_Date_MQTT;
          sat_payload += loc_GPS_Time_MQTT;
          sat_payload += "\"";
          sat_payload += "}";

          comma_check = 1;
        }
      }

      loc_lattitude = SN01.getLatitude();
      loc_longitude = SN01.getLongitude();

      if (comma_check == 1) {
        sat_payload += ",";
      }
      sat_payload += "\"Location\":["; sat_payload += String(SN01.getLatitude() * 0.0000001, 5);  sat_payload += ","; sat_payload += String(SN01.getLongitude() * 0.0000001, 5); sat_payload += "]"; comma_check = 1;

      loc_altitude  = SN01.getAltitude();
      if (comma_check == 1) {
        sat_payload += ",";
      }
      sat_payload += "\"Altitude(m)\":";   sat_payload += loc_altitude; comma_check = 1;

      loc_sog = SN01.getSOG();
      if (comma_check == 1) {
        sat_payload += ",";
      }
      sat_payload += "\"SOG(m/s)\":";   sat_payload += loc_sog; comma_check = 1;

      loc_cog = SN01.getCOG();
      if (comma_check == 1) {
        sat_payload += ",";
      }
      sat_payload += "\"COG(Deg)\":";   sat_payload += loc_cog; comma_check = 0;

      sat_payload += "},";
    } else {
      sat_payload += "\"STATUS\":\"OFFLINE\"";
      sat_payload += "},";
    }
  }

  // Get TimeStamp
  getTimeStamp();

  sat_payload += "\"Timestamp\":{";
  sat_payload += "\"Created\":\"";
  sat_payload += timeStamp;
  sat_payload += "\"";
  sat_payload += "}";

  sat_payload += "},";

  sat_payload += "\"SAT\": {";

  sat_payload += "\"SW01\": {";
  tempString = s.SW01_T;
  if (strcmp(tempString.c_str(), "NULL") != 0) {
    sat_payload += "\"Temperature(C)\":"; sat_payload += tempString; comma_check = 1;
  }
  tempString = s.SW01_H;
  if (strcmp(tempString.c_str(), "NULL") != 0) {
    if (comma_check == 1)
    {
      sat_payload += ",";
    }
    sat_payload += "\"Humidity(%)\":";    sat_payload += tempString; comma_check = 1;
  }
  tempString = s.SW01_P;
  if (strcmp(tempString.c_str(), "NULL") != 0) {
    if (comma_check == 1) {
      sat_payload += ",";
    }
    sat_payload += "\"Pressure(Pa)\":";   sat_payload += tempString; comma_check = 1;
  }
  comma_check = 0;
  sat_payload += "},";

  sat_payload += "\"SI01\": {";
  tempString = s.SI01_GF;
  if (strcmp(tempString.c_str(), "NULL") != 0) {
    sat_payload += "\"G-Force\":";   sat_payload += tempString; comma_check = 1;
  }
  tempString = s.SI01_R;
  if (strcmp(tempString.c_str(), "NULL") != 0) {
    if (comma_check == 1) {
      sat_payload += ",";
    }
    sat_payload += "\"Roll(Deg)\":";   sat_payload += tempString; comma_check = 1;
  }
  tempString = s.SI01_P;
  if (strcmp(tempString.c_str(), "NULL") != 0) {
    if (comma_check == 1) {
      sat_payload += ",";
    }
    sat_payload += "\"Pitch(Deg)\":";   sat_payload += tempString; comma_check = 1;
  }
  comma_check = 0;
  sat_payload += "},";

  sat_hdop = s.SN01_HDOP;
  sat_NumSats = s.SN01_SAT;
  sat_payload += "\"SN01\": {";
  char converthdop[10];
  strcpy(converthdop, sat_hdop.c_str());
  float floathdop = atof(converthdop);
  //Serial.println(floathdop, 2);
  if (((floathdop) < 5.0) && (strcmp(sat_hdop.c_str(), "NULL") != 0)) {
    sat_payload += "\"STATUS\":\"ONLINE\"";
    sat_payload += ",";
    sat_date = s.SN01_D;
    sat_time = s.SN01_T;
    if ((strcmp(sat_date.c_str(), "NULL") != 0) && (strcmp(sat_time.c_str(), "NULL") != 0)) {
      memset(sat_GPS_Date_temp, '\0', sizeof(sat_GPS_Date_temp));
      memset(sat_GPS_Date_MQTT, '\0', sizeof(sat_GPS_Date_MQTT));

      strcpy(sat_GPS_Date_temp, sat_date.c_str());

      if (sat_GPS_Date_temp[1] == 0x00) {
        // do nothing
      } else if (sat_GPS_Date_temp[5] == 0x00) {
        sprintf(sat_GPS_Date_MQTT, "20%c%c-%c%c-0%cT", sat_GPS_Date_temp[3], sat_GPS_Date_temp[4], sat_GPS_Date_temp[1], sat_GPS_Date_temp[2], sat_GPS_Date_temp[0]);
      } else {
        sprintf(sat_GPS_Date_MQTT, "20%c%c-%c%c-%c%cT", sat_GPS_Date_temp[4], sat_GPS_Date_temp[5], sat_GPS_Date_temp[2], sat_GPS_Date_temp[3], sat_GPS_Date_temp[0], sat_GPS_Date_temp[1]);
      }

      memset(sat_GPS_Time_temp, '\0', sizeof(sat_GPS_Time_temp));
      memset(sat_GPS_Time_MQTT, '\0', sizeof(sat_GPS_Time_MQTT));

      strcpy(sat_GPS_Time_temp, sat_time.c_str());

      if (sat_GPS_Time_temp[1] == 0x00) {
        // do nothing
      } else if (sat_GPS_Time_temp[4] == 0x00) {
        sprintf(sat_GPS_Time_MQTT, "00:%c%c:%c%c", sat_GPS_Time_temp[0], sat_GPS_Time_temp[1], sat_GPS_Time_temp[2], sat_GPS_Time_temp[3]);
      }
      else if (sat_GPS_Time_temp[5] == 0x00) {
        sprintf(sat_GPS_Time_MQTT, "0%c:%c%c:%c%c", sat_GPS_Time_temp[0], sat_GPS_Time_temp[1], sat_GPS_Time_temp[2], sat_GPS_Time_temp[3], sat_GPS_Time_temp[4]);
      } else {
        sprintf(sat_GPS_Time_MQTT, "%c%c:%c%c:%c%c", sat_GPS_Time_temp[0], sat_GPS_Time_temp[1], sat_GPS_Time_temp[2], sat_GPS_Time_temp[3], sat_GPS_Time_temp[4], sat_GPS_Time_temp[5]);
      }

      if ((sat_GPS_Date_temp[1] != 0x00) && (sat_GPS_Time_temp[1] != 0x00)) {
        sat_payload += "\"Timestamp\":{";
        sat_payload += "\"Created\":\"";
        sat_payload += sat_GPS_Date_MQTT;
        sat_payload += sat_GPS_Time_MQTT;
        sat_payload += "\"";
        sat_payload += "}";

        comma_check = 1;
      }
    }
    sat_lattitude = s.SN01_LAT;
    sat_longitude = s.SN01_LONG;
    if ((strcmp(s.SN01_LAT.c_str(), "NULL") != 0) && (strcmp(s.SN01_LONG.c_str(), "NULL") != 0)) {
      if (comma_check == 1) {
        sat_payload += ",";
      }
      sat_payload += "\"Location\":[";
      sat_payload += s.SN01_LAT;
      sat_payload += ",";
      sat_payload += s.SN01_LONG;
      sat_payload += "]";
      comma_check = 1;
    }
    sat_altitude  = s.SN01_ALT;
    if (strcmp(sat_altitude.c_str(), "NULL") != 0) {
      if (comma_check == 1) {
        sat_payload += ",";
      }
      sat_payload += "\"Altitude(m)\":";
      sat_payload += sat_altitude;
      comma_check = 1;
    }
    sat_sog = s.SN01_SOG;
    if (strcmp(sat_sog.c_str(), "NULL") != 0) {
      if (comma_check == 1) {
        sat_payload += ",";
      }
      sat_payload += "\"SOG(m/s)\":";
      sat_payload += sat_sog;
      comma_check = 1;
    }
    sat_cog = s.SN01_COG;
    if (strcmp(sat_cog.c_str(), "NULL") != 0) {
      if (comma_check == 1) {
        sat_payload += ",";
      }
      sat_payload += "\"COG(Deg)\":";
      sat_payload += sat_cog;
      comma_check = 1;
    }

    sat_ascendrate  = s.CALC_AR;
    if ((strcmp(sat_ascendrate.c_str(), "NULL") != 0) && (strcmp(sat_ascendrate.c_str(), "NAN") != 0)) {
      if (comma_check == 1) {
        sat_payload += ",";
      }
      sat_payload += "\"Ascend Rate(m/s)\":";
      sat_payload += sat_ascendrate;
      comma_check = 1;
    }
    comma_check = 0;
    sat_payload += "},";
  } else {
    sat_payload += "\"STATUS\":\"OFFLINE\"";
    sat_payload += "},";
  }

  sat_payload += "\"RL01\": {";
  s.LOC_RSSI = String(RL0X.lastRssi(), DEC);
  loc_RSSI = s.LOC_RSSI;
  if (strcmp(loc_RSSI.c_str(), "NULL") != 0) {
    if (comma_check == 1) {
      sat_payload += ",";
    }
    sat_payload += "\"GS RSSI(dB)\":";
    sat_payload += loc_RSSI;
    comma_check = 1;
  }
  sat_RSSI = s.SAT_RSSI;
  if (strcmp(sat_RSSI.c_str(), "NULL") != 0) {
    if (comma_check == 1) {
      sat_payload += ",";
    }
    sat_payload += "\"Satellite RSSI(dB)\":";
    sat_payload += sat_RSSI;
    comma_check = 1;
  }
  comma_check = 0;
  sat_payload += "},";

  // Get TimeStamp
  getTimeStamp();

  sat_payload += "\"Timestamp\":{";
  sat_payload += "\"Captured\":\"";
  sat_payload += timeStamp;
  sat_payload += "\"";
  sat_payload += "}";

  sat_payload += "}";
  sat_payload += "}";

  // check mqtt connection
  reconnect();

  // Send loc_payload
  char sat_data[1800];

  sat_payload.toCharArray(sat_data, 1800);
  reconnect();
  Serial.println();
  Serial.println("Publishing to MQTT Server...");
  Serial.print("Connection State :");
  Serial.print(" [RC : ");
  Serial.print(client.state());
  Serial.println("]");
  Serial.print("Topic: ");
  Serial.println(topic_TOAST);
  Serial.println("Satellite_Payload : ");
  Serial.println(sat_data);
  unsigned int length_SAT = strlen(sat_data);
  if (client.publish(topic_TOAST, sat_data, length_SAT)) {
    Serial.println("[PUBLISHED]");
    digitalWrite(CW01_RED, LOW);
    digitalWrite(CW01_GREEN, HIGH);
  } else {
    Serial.print("[FAILED]");
    Serial.print(" [RC : ");
    Serial.print(client.state());
    Serial.println("]");
    digitalWrite(CW01_RED, HIGH);
    digitalWrite(CW01_GREEN, LOW);
  }
  Serial.println();
  lastSend = millis();
}


