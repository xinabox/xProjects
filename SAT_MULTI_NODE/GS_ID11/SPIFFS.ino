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

void LOAD_SAVE_DATA(void) {
  File versionFile = SPIFFS.open("/version.json", "r");
  if (SPIFFS.begin()) {
    Serial.println("*WM: Searching for version.json");
    if (SPIFFS.exists("/version.json")) {
      //file exists, reading and loading
      File versionFile = SPIFFS.open("/version.json", "r");
      if (versionFile) {
        Serial.println("*WM: opened version file");
        size_t size = versionFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf1(new char[size]);
        versionFile.readBytes(buf1.get(), size);
        DynamicJsonBuffer jsonBuffer1;
        JsonObject& json1 = jsonBuffer1.parseObject(buf1.get());
        Serial.println("*WM: Parsed json");
        json1.printTo(Serial);
        Serial.println();
        if (json1.success()) {
          strcpy(XINABOX_SOFTWARE_REV, json1["XINABOX_SOFTWARE_REV"]);
        } else {
          Serial.println("*WM: Loading of JSON file failed");
        }
        versionFile.close();
        if (!strcmp(VERSION_REV, XINABOX_SOFTWARE_REV)) {
          Serial.println("*WM: Latest Version Running");
          Serial.println("*WM: Trying to load Saved data");
          LOAD_CONFIG_DATA();
        } else {
          Serial.print("*WM: New Version Detected : V");
          Serial.println(VERSION_REV);
          Serial.print("*WM: Cleaning FS for new config : ");
          SPIFFS.format();
          Serial.println("[DONE]");
        }
      } else {
        Serial.println("*WM: failed to open version.json");
      }
    } else {
      Serial.println("*WM: version.json not found");
      Serial.print("*WM: Cleaning FS for new Config : ");
      SPIFFS.format();
      Serial.println("[DONE]");
    }
  } else {
    Serial.println("*WM: failed to mount FS");
    SPIFFS.format();
  }
}

void LOAD_CONFIG_DATA(void) {
  //read configuration from FS json
  File deviceFile = SPIFFS.open("/device.json", "r");
  if (SPIFFS.begin()) {
    // Load Device Specific Data from SPIFFS
    Serial.println("*WM: Searching for device.json");
    if (SPIFFS.exists("/device.json")) {
      //file exists, reading and loading
      File deviceFile = SPIFFS.open("/device.json", "r");
      if (deviceFile) {
        Serial.println("*WM: opened device file");
        size_t size = deviceFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf2(new char[size]);
        deviceFile.readBytes(buf2.get(), size);
        DynamicJsonBuffer jsonBuffer2;
        JsonObject& json2 = jsonBuffer2.parseObject(buf2.get());
        Serial.println("*WM: Parsed json:");
        json2.printTo(Serial);
        Serial.println();
        if (json2.success()) {
          strcpy(XINABOX_DEVICENAME, json2["XINABOX_DEVICENAME"]);
          strcpy(XINABOX_LATITUDE, json2["XINABOX_LATITUDE"]);
          strcpy(XINABOX_LONGITUDE, json2["XINABOX_LONGITUDE"]);
          strcpy(XINABOX_ALTITUDE, json2["XINABOX_ALTITUDE"]);
          strcpy(XINABOX_IN_OUT, json2["XINABOX_IN_OUT"]);
          strcpy(XINABOX_ORGANIZATION, json2["XINABOX_ORGANIZATION"]);
          strcpy(XINABOX_INDEX, json2["XINABOX_INDEX"]);
        } else {
          Serial.println("*WM: Loading of JSON file failed");
        }
        deviceFile.close();
      } else {
        Serial.println("*WM: failed to open device.json");
      }
    } else {
      Serial.println("*WM: device.json not found");
    }

    // Load Blynk Specific Data from SPIFFS
    Serial.println("*WM: Searching for blynk.json");
    if (SPIFFS.exists("/blynk.json")) {
      //file exists, reading and loading
      File blynkFile = SPIFFS.open("/blynk.json", "r");
      if (blynkFile) {
        Serial.println("*WM: opened mqtt file");
        size_t size = blynkFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf4(new char[size]);
        blynkFile.readBytes(buf4.get(), size);
        DynamicJsonBuffer jsonBuffer4;
        JsonObject& json4 = jsonBuffer4.parseObject(buf4.get());
        Serial.println("*WM: Parsed json");
        json4.printTo(Serial);
        Serial.println();
        if (json4.success()) {
          strcpy(XINABOX_BLYNK_AUTH, json4["XINABOX_BLYNK_AUTH"]);
        } else {
          Serial.println("*WM: Loading of JSON file failed");
        }
        blynkFile.close();
      } else {
        Serial.println("*WM: failed to open blynk.json");
      }
    } else {
      Serial.println("*WM: blynk.json not found");
    }
  } else {
    Serial.println("*WM: failed to mount FS");
  }
}

void LOAD_NEW_USER_DATA(void) {
  //read updated parameters
  if (wifiManager.newDeviceData()) {
    sprintf(XINABOX_DEVICENAME,  wifiManager.getDeviceData(1).c_str());
    sprintf(XINABOX_LATITUDE, wifiManager.getDeviceData(2).c_str());
    sprintf(XINABOX_LONGITUDE, wifiManager.getDeviceData(3).c_str());
    sprintf(XINABOX_ALTITUDE, wifiManager.getDeviceData(4).c_str());
    sprintf(XINABOX_IN_OUT, wifiManager.getDeviceData(6).c_str());
    sprintf(XINABOX_INDEX, wifiManager.getDeviceData(7).c_str());
    sprintf(XINABOX_ORGANIZATION, wifiManager.getDeviceData(8).c_str());
  }
  if (wifiManager.newBlynkData()) {
    sprintf(XINABOX_BLYNK_AUTH, wifiManager.getBlynkData(3).c_str());
  }
}

void JSON_FILE_UPDATES(void) {
  //save the custom parameters to FS
  if (strcmp(VERSION_REV, XINABOX_SOFTWARE_REV)) {
    sprintf(XINABOX_SOFTWARE_REV,VERSION_REV);
    Serial.print("*WM: updating version.json : ");
    DynamicJsonBuffer jsonBuffer1;
    JsonObject& json1 = jsonBuffer1.createObject();
    json1["XINABOX_SOFTWARE_REV"] = XINABOX_SOFTWARE_REV;
    File versionFile = SPIFFS.open("/version.json", "w");
    if (!versionFile) {
      Serial.print("[FAILED]");
      Serial.println(" Failed to open version.json for writing");
    } else {
      Serial.println("[DONE]");
      Serial.println("*WM: New parsed version");
      json1.printTo(Serial);
      json1.printTo(versionFile);
      Serial.println();
      versionFile.close();
      //end save
    }
  }

  if (wifiManager.newDeviceData()) {
    Serial.print("*WM: updating device.json fields : ");
    DynamicJsonBuffer jsonBuffer2;
    JsonObject& json2 = jsonBuffer2.createObject();
    json2["XINABOX_DEVICENAME"] = XINABOX_DEVICENAME;
    json2["XINABOX_LATITUDE"] = XINABOX_LATITUDE;
    json2["XINABOX_LONGITUDE"] = XINABOX_LONGITUDE;
    json2["XINABOX_ALTITUDE"] = XINABOX_ALTITUDE;
    json2["XINABOX_IN_OUT"] = XINABOX_IN_OUT;
    json2["XINABOX_INDEX"] = XINABOX_INDEX;
    json2["XINABOX_ORGANIZATION"] = XINABOX_ORGANIZATION;
    File deviceFile = SPIFFS.open("/device.json", "w");
    if (!deviceFile) {
      Serial.print("[FAILED]");
      Serial.println("*WM: failed to open device.json for writing");
    } else {
      Serial.println("[DONE]");
      Serial.println("*WM: New parsed config");
      json2.printTo(Serial);
      json2.printTo(deviceFile);
      Serial.println();
      deviceFile.close();
      //end save
    }
  }

  if (wifiManager.newBlynkData()) {
    Serial.print("*WM: updating blynk.json fields : ");
    DynamicJsonBuffer jsonBuffer4;
    JsonObject& json4 = jsonBuffer4.createObject();
    json4["XINABOX_BLYNK_AUTH"] = XINABOX_BLYNK_AUTH;
    File blynkFile = SPIFFS.open("/blynk.json", "w");
    if (!blynkFile) {
      Serial.print("[FAILED]");
      Serial.println("*WM: failed to open blynk.json for writing");
    } else {
      Serial.println("[DONE]");
      json4.printTo(blynkFile);
      Serial.println();
      blynkFile.close();
      //end save
    }
  }
}
