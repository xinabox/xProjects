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

/***
  Function to start the Radio
  @param FREQ, the frequency of the Radio
 ***/
void startRL0X(float FREQ) {
  RL0X.setFrequency(FREQ);
}

void gsReceive(uint8_t cmd) {
  // clear the buffer
  memset(satBuffer, 0, sizeof(satBuffer));
  for (int i = 0; i < 3; i++) {
    if (RL0X.waitAvailableTimeout(3000)) {
      len = sizeof(satBuffer);
      if (RL0X.recv(satBuffer, &len)) {
        i = 3;
        len = sizeof(satBuffer);
        //Serial.print("Reply : ");
        //Serial.println((char*)satBuffer);
        char c = 0;
        for (byte i = 0; i < 32; i++) {
          c = satBuffer[i];
          if ( c == '$') {
            s.bufferidx = 0;
            s.buffer[s.bufferidx++] = c;
            delay(1);
            continue;
          }
          if ( c == '*') {
            s.buffer[s.bufferidx++] = 0;
            delay(1);
            parseSatDATA();
          } else {
            if (s.bufferidx < 32) {
              s.buffer[s.bufferidx++] = c;
              delay(1);
            } else {
              s.bufferidx = 0;
            }
          }
        }
      } else {
        s.SAT_STATUS = "ERR";
      }
    } else {
      SN01.poll();
      gsSend(cmd);
      s.SAT_STATUS = "ERR";
    }
  }
}

/***
  Function to send command to Satelittle
  @param CMD, command recieved over I2C
 ***/
void gsSend(uint8_t cmd) {
  gsSend(cmd, 0, 0);
}

/***
  Function to send command to Satelittle
  @param cmd, command to send
  @param channel, burnwaire channel to burn
  @param burn_time_s, amount of time(s) to burn the channel
 ***/
void gsSend(uint8_t cmd, uint8_t channel, uint8_t burn_time_s) {
  I2C_BUF[0] = cmd;
  I2C_BUF[1] = channel;
  I2C_BUF[2] = burn_time_s;
  delay(100);
  RL0X.send(I2C_BUF, sizeof(I2C_BUF));
  // cler the buffer
  memset(I2C_BUF, 0, sizeof(I2C_BUF));
}



