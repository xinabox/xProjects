/******************************************************************************
    This is an example the RL01 to act as a state machine

    You can buy one on our store!
    -----> https://xinabox.cc/RL01/

    Currently Supported on the following ☒CHIP:
    - RL01/RL02/RL01
    - CW01
    - PB04
    - SW01
    - SL01
    - OC01
    - SN01
    - SI01

    The sensor communicates over the I2C Bus.

******************************************************************************/

/***
  Function to determine incoming command from Radio
  @param CMD, string of HEX command reviced by radio
 ***/
void satCMD(uint8_t CMD) {
  switch (CMD) {
    case 1:
      SW01_BUFFER();
      satREPLY();
      break;

    case 2:
      SI01_BUFFER();
      satREPLY();
      break;

    case 3:
      SL01_BUFFER();
      satREPLY();
      break;

    case 4:
      RL01_BUFFER();
      satREPLY();
      break;

    case 5:
      GPS1_BUFFER();
      satREPLY();
      break;

    case 6:
      GPS2_BUFFER();
      satREPLY();
      break;

    case 7:
      GPS3_BUFFER();
      satREPLY();
      break;

    case 8:
      GPS4_BUFFER();
      satREPLY();
      break;

    case ACK:
      SAT_STATUS_BUFFER();
      satREPLY();
      break;

    default:
      sprintf(satBuffer, "%s", "ERR");
      satREPLY();
      break;
  }
}

// Build SW01 Buffer
void SW01_BUFFER(void) {
  // clear buffers
  memset(satBuffer, 0, sizeof(satBuffer));

  String satResponse = "";
  satResponse += "$SW01,";
  satResponse += String(SW01.getTempC(), 1);
  satResponse += ",";
  satResponse += String(SW01.getHumidity(), 0);
  satResponse += ",";
  satResponse += String(SW01.getPressure(), 0);
  satResponse += ",*";

  satResponse.toCharArray(satBuffer, sizeof(satBuffer));
}

// Build SI01 Buffer
void SI01_BUFFER(void) {
  // clear buffers
  memset(satBuffer, 0, sizeof(satBuffer));

  String satResponse = "";

  satResponse += "$SI01,";
  satResponse += String(SI01.getRoll(), 2);
  satResponse += ",";
  satResponse += String(SI01.getPitch(), 2);
  satResponse += ",";
  satResponse += String(SI01.getGForce(), 2);
  satResponse += ",*";

  satResponse.toCharArray(satBuffer, sizeof(satBuffer));
}

// Build SL01 buffer
void SL01_BUFFER(void) {
  // clear buffers
  memset(satBuffer, 0, sizeof(satBuffer));

  String satResponse = "";

  satResponse += "$SL01,";
  satResponse += String(SL01.getUVA(), 0);
  satResponse += ",";
  satResponse += String(SL01.getUVB(), 0);
  satResponse += ",";
  float uv_index = constrain(SL01.getUVIndex(), 0, 12);
  satResponse += String((int)uv_index);
  satResponse += ",";
  satResponse += String(SL01.getLUX(), 0);
  satResponse += ",*";

  satResponse.toCharArray(satBuffer, sizeof(satBuffer));
}

// Build RL01 buffer
void RL01_BUFFER(void) {
  // clear buffers
  memset(satBuffer, 0, sizeof(satBuffer));

  String satResponse = "";

  satResponse += "$RL03,";
  satResponse += String(RL0X.lastRssi(), DEC);
  satResponse += ",*";

  satResponse.toCharArray(satBuffer, sizeof(satBuffer));
}

// Build GPS1 buffer incl - Time and Date
void GPS1_BUFFER(void) {
  // clear buffers
  memset(satBuffer, 0, sizeof(satBuffer));

  String satResponse =  "$GPS1,";

  if ((SN01.getHDOP() < 5) && (SN01.getHDOP() > 0)) {
    satResponse +=  SN01.getDate();
    satResponse +=  ",";
    satResponse +=  String(SN01.getTime() * 0.01, 0);
    newTime = SN01.getTime();
    satResponse +=  ",*";
    satResponse.toCharArray(satBuffer, sizeof(satBuffer));
  } else {
    satResponse +=  "0,0";
    satResponse +=  ",*";
    satResponse.toCharArray(satBuffer, sizeof(satBuffer));
  }
}

// Build GPS2 buffer incl - Latitude and Longitude
void GPS2_BUFFER(void) {
  // clear buffers
  memset(satBuffer, 0, sizeof(satBuffer));

  String satResponse =  "$GPS2,";

  if ((SN01.getHDOP() < 5) && (SN01.getHDOP() > 0)) {
    satResponse +=  String(SN01.getLatitude() * 0.0000001, 5);
    satResponse +=  ",";
    satResponse +=  String(SN01.getLongitude() * 0.0000001, 5);
    satResponse +=  ",*";
    satResponse.toCharArray(satBuffer, sizeof(satBuffer));
  } else {
    satResponse +=  "0,0";
    satResponse +=  ",*";
    satResponse.toCharArray(satBuffer, sizeof(satBuffer));
  }
}

// Build GPS3 buffer incl - Altitude, SOG, COG, HDOP and Satelittes Conncted
void GPS3_BUFFER(void) {
  // clear buffers
  memset(satBuffer, 0, sizeof(satBuffer));

  String satResponse =  "$GPS3,";
  satResponse +=  String((int)SN01.getHDOP());
  satResponse +=  ",";
  satResponse +=  String(SN01.getSatelitesConnected(), HEX);
  satResponse +=  ",";

  if ((SN01.getHDOP() < 5) && (SN01.getHDOP() > 0)) {
    satResponse +=  "1,";
    satResponse +=  String(SN01.getAltitude());
    newAlt = SN01.getAltitude();
    satResponse +=  ",";
    satResponse +=  String((float)SN01.getSOG(), 1);
    satResponse +=  ",";
    satResponse +=  String((float)SN01.getCOG(), 1);
    satResponse +=  ",*";

    satResponse.toCharArray(satBuffer, sizeof(satBuffer));
  } else {
    satResponse +=  "0";
    satResponse +=  ",*";
    satResponse.toCharArray(satBuffer, sizeof(satBuffer));
  }
}

// Build GPS4 buffer incl - Ascent Rate
void GPS4_BUFFER(void) {
  // clear buffers
  memset(satBuffer, 0, sizeof(satBuffer));

  String satResponse = "";

  satResponse +=  "$GPS4,";

  if ((SN01.getHDOP() < 5) && (SN01.getHDOP() > 0)) {
    ascendRate = ((newAlt - oldAlt) / ((newTime - oldTime) / 1000));
    if (isnan(ascendRate)) {
      satResponse += String(ascendRate, 2);
    } else {
      satResponse += String(0.0, 2);
    }
    oldAlt = newAlt;
    oldTime = newTime;
    satResponse +=  ",*";
    satResponse.toCharArray(satBuffer, sizeof(satBuffer));
  } else {
    satResponse +=  "0";
    satResponse +=  ",*";
    satResponse.toCharArray(satBuffer, sizeof(satBuffer));
  }
}

// Build SAT_STATUS Buffer
void SAT_STATUS_BUFFER(void) {
  // clear buffers
  memset(satBuffer, 0, sizeof(satBuffer));
  memset(append, 0, sizeof(append));

  String satResponse = "";
  satResponse += "$STAT,";
  satResponse += String(RL0X.lastRssi(), DEC);
  satResponse += ",*,";

  satResponse.toCharArray(satBuffer, sizeof(satBuffer));
}





