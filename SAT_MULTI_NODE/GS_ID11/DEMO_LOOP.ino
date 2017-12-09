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

void DEMO_PHASE2(void) {
  //check server connection
  if ((millis() - lastServerCheck) > 5000/*SERVER_CHECK_INTERVAL*/) {
    if (!client.connected()) {
      reconnect();
      BLYNK_LOOP();
    }
    lastServerCheck = millis();
  }

  if ((millis() - satSendInterval) > 5000/*PUBLISH_INTERVAL*/) {
    // poll the connected sensors
    POLL_PHASE2();

    satSendInterval = millis();

    checkSAT(TO_ID1);
    if (strcmp(s.SAT_STATUS.c_str(),"ERR") != 0) {
      reconnect();
      getTOAST(TO_ID1);
      Blynk.virtualWrite(V20, s.SAT_STATUS);
      STEM_LED.on();
    } else {
      Blynk.virtualWrite(V20, "NO COMMS");
      STEM_LED.off();
    }

    checkSAT(TO_ID2);
    if (strcmp(s.SAT_STATUS.c_str(),"ERR") != 0) {
      reconnect();
      getTOAST(TO_ID2);
      Blynk.virtualWrite(V21, s.SAT_STATUS);
      COOKIE_LED.on();
    } else {
      Blynk.virtualWrite(V21, "NO COMMS");
      COOKIE_LED.off();
    }

    checkSAT(TO_ID3);
    if (strcmp(s.SAT_STATUS.c_str(),"ERR") != 0) {
      reconnect();
      getTOAST(TO_ID3);
      Blynk.virtualWrite(V22, s.SAT_STATUS);
      TOAST_LED.on();
    } else {
      Blynk.virtualWrite(V22, "NO COMMS");
      TOAST_LED.off();
    }
  }

  if ((millis() - tick_OD01) > 10000/*OD01_PRINT_INTERVAL*/) {
    // Display Data on OLED
    displayOLED();
    tick_OD01 = millis();
  }

  if ((millis() - tick_SN01) > 100) { /*GPS POLL*/
    // Display Data on OLED
    if (pingADDRESS(0x42) == true) {
      SN01.poll();
    }
    tick_SN01 = millis();
  }

  client.loop();
}

void checkSAT(uint8_t ID)
{
  setNewHeader(ID);
  satData(ACK);
}

