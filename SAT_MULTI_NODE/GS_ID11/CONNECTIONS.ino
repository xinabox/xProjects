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

// connect to WiFi network
boolean WIFI_connect(void) {
  if (WiFi.status() != WL_CONNECTED) {
    digitalWrite(CW01_GREEN, LOW);
    digitalWrite(CW01_BLUE, LOW);
    // Connect to WiFi access point.
    Serial.println(); Serial.println();
    Serial.print("*WM: Wi-Fi Connection");

    // Start ESP8266 STA mode
    WiFi.begin();
    tick_WiFi = 0;
    // check connection status
    while ((WiFi.status() != WL_CONNECTED) && (tick_WiFi < 3)) {
      digitalWrite(CW01_RED, HIGH);
      delay(10);
      digitalWrite(CW01_RED, LOW);
      delay(10);
      Serial.print(".");
      tick_WiFi++;
    }
    if (WiFi.status() == WL_CONNECTED) {
      digitalWrite(CW01_GREEN, HIGH);
      Serial.println("[DONE]");
      return true;
    } else {
      digitalWrite(CW01_GREEN, LOW);
      Serial.println("[FAILED]");
      return false;
    }
  } else {
    digitalWrite(CW01_GREEN, HIGH);
    return true;
  }
}

// connect to MQTT broker
void MQTT_connect(void) {
  client.setServer(XINABOX_SERVER.c_str() , XINABOX_SERVERPORT_1);
}

// poll connection to MQTT broker
void reconnect(void) {
  // Loop until we're reconnected
  tick_MQTT = 0;
  if (WIFI_connect()) {
    if (!client.connected()) {
      Serial.print("\n*WM: Connecting to MQTT Server node ...[PORT:80]");
      // use MQTT SERVERPORT 1883
      while (!client.connected() && (tick_MQTT < 5) ) {
        tick_MQTT++;
        digitalWrite(CW01_BLUE, HIGH);
        // Attempt to connect (clientId, username, password)
        if ( client.connect(CLIENT_ID.c_str(), XINABOX_USERNAME.c_str(), XINABOX_PASSWORD.c_str() ) ) {
          Serial.println("[DONE]");
          setupComplete = 1;
          MQTT_CONN_E = false;
        }
        if (client.connected()) {
          client.loop();
        }
        digitalWrite(CW01_BLUE, LOW);
      }
      if(!client.connected()){
        Serial.println("[FAILED]");
      }
      // use alternate MQTT SERVERPORT 80
      if (setupComplete == 0) {
        tick_MQTT = 0;
        client.setServer(XINABOX_SERVER.c_str() , XINABOX_SERVERPORT_2);
        Serial.print("\n*WM: Connecting to MQTT Server node ...[PORT:1883]");
        while (!client.connected() && (tick_MQTT < 5) ) {
          tick_MQTT++;
          digitalWrite(CW01_BLUE, HIGH);
          // Attempt to connect (clientId, username, password)
          if ( client.connect(CLIENT_ID.c_str(), XINABOX_USERNAME.c_str(), XINABOX_PASSWORD.c_str() ) ) {
            Serial.println("[DONE]");
            setupComplete = 1;
            MQTT_CONN_E = false;
          }
          if (client.connected()) {
            client.loop();
          }
          digitalWrite(CW01_BLUE, LOW);
        }
      }
      if (!client.connected()) {
        Serial.println("[FAILED]");
        MQTT_CONN_E = ERROR_OCCURED = true;
      }
    } else {
      MQTT_CONN_E = false;
    }
  }
}

// connect to blynk
void BLYNK_CONNECT(void) {
  tick_BLYNK = 0;
  uint8_t blynk_connected = 0;

  if (USE_BLYNK == true) {
    if (!Blynk.connected()) {
      Serial.print("\n*WM: Connecting to Blynk Server...[PORT:80]");
      // use alternate BLYNKSERVER port 80
      while (!Blynk.connected() && (tick_BLYNK < 5)) {
        Blynk.config(XINABOX_BLYNK_AUTH, XINABOX_BLYNK.c_str(), XINABOX_BLYNKPORT_2);
        Blynk.connect(1000);
        tick_BLYNK++;
        if (Blynk.connected()) {
          Serial.println("[DONE]");
          blynk_connected = 1;
          tick_BLYNK = 11;
        }
      }
      if(!Blynk.connected()){
        Serial.println("[FAILED][PORT:80]");
      }
      if (blynk_connected == 0) {
        tick_BLYNK = 0;
        Serial.print("\n*WM: Connecting to Blynk Server...[PORT:8443]");
        // use default BLYNKSERVER port 8443
        while (!Blynk.connected() && (tick_BLYNK < 5)) {
          Blynk.config(XINABOX_BLYNK_AUTH, XINABOX_BLYNK.c_str(), XINABOX_BLYNKPORT_1);
          Blynk.connect(1000);
          tick_BLYNK++;
          if (Blynk.connected()) {
            Serial.println("[DONE]");
            blynk_connected = 1;
            tick_BLYNK = 11;
          }
        }
      }
      if (!Blynk.connected()) {
        Serial.println("[FAILED][PORT:844]");
      }
    } else {
      // do nothing
    }
  }
}

