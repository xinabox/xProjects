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

void parseSatDATA(void) {
  char *parseptr;

  if (strncmp(s.buffer, "$SW01", 5) == 0) {
    //Serial.println(s.buffer);
    parseptr = strchr(s.buffer, ',') + 1;
    s.SW01_T = parseBuffer(parseptr);
    parseptr = strchr(parseptr, ',') + 1;
    s.SW01_H = parseBuffer(parseptr);
    parseptr = strchr(parseptr, ',') + 1;
    s.SW01_P = parseBuffer(parseptr);

  } else if (strncmp(s.buffer, "$SL01", 5) == 0) {
    //Serial.println(s.buffer);
    parseptr = strchr(s.buffer, ',') + 1;
    s.SL01_A = parseBuffer(parseptr);
    parseptr = strchr(parseptr, ',') + 1;
    s.SL01_B = parseBuffer(parseptr);
    parseptr = strchr(parseptr, ',') + 1;
    s.SL01_I = parseBuffer(parseptr);
    parseptr = strchr(parseptr, ',') + 1;
    s.SL01_L = parseBuffer(parseptr);

  } else if (strncmp(s.buffer, "$SI01", 5) == 0) {
    //Serial.println(s.buffer);
    parseptr = strchr(s.buffer, ',') + 1;
    s.SI01_R = parseBuffer(parseptr);
    parseptr = strchr(parseptr, ',') + 1;
    s.SI01_P = parseBuffer(parseptr);
    parseptr = strchr(parseptr, ',') + 1;
    s.SI01_GF = parseBuffer(parseptr);

  } else if (strncmp(s.buffer, "$PB04", 5) == 0) {
    //Serial.println(s.buffer);
    parseptr = strchr(s.buffer, ',') + 1;
    s.PB04_V = parseBuffer(parseptr);
    parseptr = strchr(parseptr, ',') + 1;
    s.PB04_C = parseBuffer(parseptr);

  } else if (strncmp(s.buffer, "$CR0X", 5) == 0) {
    //Serial.println(s.buffer);
    parseptr = strchr(s.buffer, ',') + 1;
    s.SAT_RSSI = parseBuffer(parseptr);

  } else if (strncmp(s.buffer, "$RL03", 5) == 0) {
    //Serial.println(s.buffer);
    parseptr = strchr(s.buffer, ',') + 1;
    s.SAT_RSSI = parseBuffer(parseptr);

  } else if (strncmp(s.buffer, "$RL01", 5) == 0) {
    //Serial.println(s.buffer);
    parseptr = strchr(s.buffer, ',') + 1;
    s.SAT_RSSI = parseBuffer(parseptr);

  } else if (strncmp(s.buffer, "$RL0X", 5) == 0) {
    //Serial.println(s.buffer);
    parseptr = strchr(s.buffer, ',') + 1;
    s.SAT_RSSI = parseBuffer(parseptr);

  } else if (strncmp(s.buffer, "$GPS1", 5) == 0) {
    //Serial.println(s.buffer);
    if (s.SN01_STAT != "0") {
      parseptr = strchr(s.buffer, ',') + 1;
      s.SN01_D = parseBuffer(parseptr);
      parseptr = strchr(parseptr, ',') + 1;
      s.SN01_T = parseBuffer(parseptr);
    }

  } else if (strncmp(s.buffer, "$GPS2", 5) == 0) {
    //Serial.println(s.buffer);
    if (s.SN01_STAT != "0") {
      parseptr = strchr(s.buffer, ',') + 1;
      s.SN01_LAT = parseBuffer(parseptr);
      parseptr = strchr(parseptr, ',') + 1;
      s.SN01_LONG = parseBuffer(parseptr);
    }

  } else if (strncmp(s.buffer, "$GPS3", 5) == 0) {
    //Serial.println(s.buffer);
    parseptr = strchr(s.buffer, ',') + 1;
    s.SN01_HDOP = parseBuffer(parseptr);
    parseptr = strchr(parseptr, ',') + 1;
    s.SN01_SAT = parseBuffer(parseptr);
    if(s.SN01_SAT == "a"){
      s.SN01_SAT = "10";
    } else if(s.SN01_SAT == "b"){
      s.SN01_SAT = "11";
    } else if(s.SN01_SAT == "c"){
      s.SN01_SAT = "12";
    } else if(s.SN01_SAT == "d"){
      s.SN01_SAT = "13";
    } else if(s.SN01_SAT == "e"){
      s.SN01_SAT = "14";
    } else if(s.SN01_SAT == "f"){
      s.SN01_SAT = "15";
    }
    parseptr = strchr(parseptr, ',') + 1;
    s.SN01_STAT = parseBuffer(parseptr);
    if (s.SN01_STAT != "0") {
      parseptr = strchr(parseptr, ',') + 1;
      s.SN01_ALT = parseBuffer(parseptr);
      parseptr = strchr(parseptr, ',') + 1;
      s.SN01_SOG = parseBuffer(parseptr);
      parseptr = strchr(parseptr, ',') + 1;
      s.SN01_COG = parseBuffer(parseptr);
    }

  } else if (strncmp(s.buffer, "$GPS4", 5) == 0) {
    //Serial.println(s.buffer);
    if (s.SN01_STAT != "0") {
      parseptr = strchr(s.buffer, ',') + 1;
      s.CALC_AR = parseBuffer(parseptr);
    }
  } else if (strncmp(s.buffer, "$STAT", 5) == 0) {
    //Serial.println(s.buffer);
    parseptr = strchr(s.buffer, ',') + 1;
    s.SAT_STATUS = parseBuffer(parseptr);
  } else {
    Serial.println("[UNKNOWN DATA]");
  }
  s.bufferidx = 0;
}


String parseBuffer(char *str) {
  char temp_str[40];

  memset(temp_str, 0, sizeof(temp_str));

  strcpy(temp_str, str);

  const char s[2] = ",";
  char *id;
  char *parse_ptr;
  delay(1);
  parse_ptr = strtok_r(temp_str, s, &id);
  //Serial.println(parse_ptr);
  return (String)parse_ptr;
}


