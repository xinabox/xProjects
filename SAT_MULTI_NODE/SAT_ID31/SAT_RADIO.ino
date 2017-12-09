/******************************************************************************
    This is an example the RL01 to act as a state machine

    You can buy one on our store!
    -----> https://xinabox.cc/products/CW01/
    -----> https://xinabox.cc/products/RL01/   

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
   Initialize radio for Statelitte
 ***/
void satRADIO(void) {
  if (!RL0X.begin()) { // <-- enter radio name here
    DEBUG_PRINT("Check the connector to CR01", true);
    while (1) {
      // Flash RED to indicate failure
      digitalWrite(CW01_RED, HIGH);
      delay(100);
      digitalWrite(CW01_RED, LOW);
      delay(100);
    }
  } else {
    // RL0X Initialized correctly
    //RL0X.setModemConfig(RL01.Bw31_25Cr48Sf512);
    RL0X.setFrequency(RL01_FREQ);
    RL0X.setTxPower(23, false);
    SET_RADIO_HEADERS(ADDR_ID, FROM_ID, TO_ID);
    DEBUG_PRINT("RL01 Init success", true);
    DEBUG_PRINT("Radio Address : ", false);
    DEBUG_PRINT(String(ADDR_ID, HEX), true);
  }
}

/***
  Function to get data from Radio
  @param packetsize, size of incoming data
 ***/
void satReceive(void) {
  if (RL0X.waitAvailableTimeout(2000)) {
    digitalWrite(CW01_BLUE, LOW);
    digitalWrite(CW01_GREEN, HIGH);
    len = sizeof(I2C_BUF);
    // Wait for a message addressed to us
    if (RL0X.recv(I2C_BUF, &len)) {
      receivedRSSI = RL0X.lastRssi();
      sendDATA = true;
      DEBUG_PRINT("CMD Received: ", false);
      DEBUG_PRINT(String(I2C_BUF[0], DEC), true);
      satCMD(I2C_BUF[0]);
      //DEBUG_PRINT("CMD : ", false);
      //Serial.println(buf[0], DEC);
    } else {
      // do nothing
    }
  }
  digitalWrite(CW01_GREEN, LOW);
  digitalWrite(CW01_BLUE, HIGH);
}

/***
  Function to send reply to Ground Station
 ***/
void satREPLY(void) {
  RL0X.send((uint8_t*)satBuffer, sizeof(satBuffer));
  DEBUG_PRINT(String("REPLY: "), false);
  DEBUG_PRINT((char*)satBuffer, true);
  Serial.println();
  
  // cler the buffer
  memset(I2C_BUF, 0, sizeof(I2C_BUF)); 
}
























