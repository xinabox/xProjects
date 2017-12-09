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

// WiFi Start Load Parameters
void WifiStartup(void) {
  // Get Saved Data from SPIFFS
  LOAD_SAVE_DATA();

  //set config save notify callback
  wifiManager.setSaveConfigCallback(saveConfigCallback);

  //reset settings - for testing
  //wifiManager.resetSettings();

  //sets timeout until configuration portal gets turned off
  //useful to make it all retry or go to sleep
  //in seconds
  wifiManager.setConfigPortalTimeout(CAPTIVE_PORTAL_TIMEOUT);

  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  String AP_name = "XINABOX_" + (String)ESP.getChipId();
  //and goes into a blocking loop awaiting configuration
  WiFi.hostname(AP_name.c_str());

  digitalWrite(CW01_BLUE, HIGH); // AP shoul be active now

  if (!wifiManager.startConfigPortal(AP_name.c_str(), "password")) {
    Serial.println("*WM: failed to connect and hit timeout");
    delay(3000);
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(5000);
  }

  //if you get here you have connected to the WiFi
  Serial.println("*WM: connected...yeey :)");

  digitalWrite(CW01_BLUE, LOW);  // AP is now off

  // check if new configs are present
  Serial.println("*WM: Checking if new User Data entered");
  
  LOAD_NEW_USER_DATA(); //(found in SPIFFS tab)
  JSON_FILE_UPDATES();

  if (XINABOX_BLYNK_AUTH[0] != 0) {
    USE_BLYNK = true;
  }
  
  Serial.print("*WM: Local IP : ");
  Serial.println(WiFi.localIP());
}

// Save config to FS
void saveConfigCallback(void) {
  Serial.println("*WM: Should save config");
  shouldSaveConfig = true;
}
