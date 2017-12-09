  /*****************************************************************************
    This is an example for the xCHIP High Altitude Balloon Kit

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

// ESP Libraries
#include <FS.h>                   //this needs to be first, or it all crashes and burns...
#include <ESP8266WiFi.h>
#include <DNSServer.h>

// Arduino Libraries
#include <PubSubClient.h>
#include <WiFiManager.h>
#include <ArduinoJson.h>
#include <NTPtimeESP.h>
#include <BlynkSimpleEsp8266.h>

// XINABOX Libraries
#include <xCore.h>
#include <xSW01.h>
#include <xSL01.h>
#include <xOD01.h>
#include <xSI01.h>
#include <xSN01.h>
#include <xRL0X.h>
#include "xDEMO.h"
#include "xBALLOON.h"
#include "xERROR.h"

/************ Global State (you don't need to change this!) ******************/
struct SENSOR_REG s;
struct CONTROL_REG c;
struct RADIO_REG r;

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient ESP_client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
PubSubClient client(ESP_client);

WiFiManager wifiManager;

/*************************** NTP Server Parameters **************************/
NTPtime NTPch("time.google.com");   // Choose server pool as required
strDateTime dateTime;

/****************************** Bylnk Parameters ****************************/
#define BLYNK_HEARTBEAT 30
WidgetMap myMap(V7);
WidgetLED STEM_LED(V23);
WidgetLED COOKIE_LED(V24);
WidgetLED TOAST_LED(V25);
/*************************** Radio ID Conf **********************************/

// Radio Defines
#define RL01_FREQ 433.0
#define RL02_FREQ 868.0
#define RL03_FREQ 915.0

// Radio GS Address
#define ADDR_ID 0x11
#define FROM_ID 0x11

// Radio ID set 1
#define TO_ID1   0x21

// Radio ID set 2
#define TO_ID2   0x31

// Radio ID Set 3
#define TO_ID3   0x41

/**************************** Sketch Code ***********************************/

char*   VERSION_REV = "1.411";
#define CAPTIVE_PORTAL_TIMEOUT 30

void setup() {
  CR0X_HERE = false;
  RL0X_HERE = false;

  // Start the I2C bus
  Serial.begin(115200);
  Wire.pins(2, 14);
  Wire.begin();
  Wire.setClockStretchLimit(15000); //Only use on ESP, the I2C on ESP is timed too narrow for most applications.
  OLED.begin();
  if (!isBOOT) {
    WiFi.mode(WIFI_OFF);
    // check which I2C devices are available
    OD01.clear();
    OD01.setScroll(false);
    OD01.print("MAC:");
    OD01.println(WiFi.macAddress());
    OD01.println("=======================");
    OD01.println("Connect to Hotspot:");
    String AP_name = " XINABOX_" + (String)ESP.getChipId();
    OD01.println(AP_name);
    OD01.println("Password is: ");
    OD01.println(" password");
    OD01.println("In your browser:");
    OD01.println(" 192.168.4.1");
    isBOOT = true;
  }

  delay(5000);
  Wire.endTransmission();
  
  CLIENT_ID = ESP.getChipId();
  CLIENT_MAC = WiFi.macAddress();

  // Create MQTT Identification Data
  CLIENT_ID.toCharArray(ServerClientID, 40);

  // Set direction of RGB Pins
  pinMode(CW01_RED, OUTPUT);
  pinMode(CW01_GREEN, OUTPUT);
  pinMode(CW01_BLUE, OUTPUT);

  // Used to reset WiFi connection Settings
  //WiFi.disconnect();
  
  RL0X.begin();
  RL0X.setFrequency(RL01_FREQ);
  RL0X.setTxPower(23, false);
  RL0X.setThisAddress(ADDR_ID);
  RL0X.setHeaderFrom(FROM_ID);

  // create Captive Portal
  WifiStartup();

  // connect to MQTT broker
  MQTT_connect();

  // check wifi connection
  //WIFI_connect();

  OD01.clear();
  OD01.print("Unit Name:\n ");
  OD01.println(XINABOX_DEVICENAME);
  OD01.print("ID:\n ");
  OD01.println(CLIENT_ID);
  OD01.print("MAC:\n ");
  OD01.println(WiFi.macAddress());
  OD01.print("Index:\n ");
  OD01.println(XINABOX_INDEX);
  OD01_timeout = millis();
  delay(5000);

  // Create MQTT Topic
  for (size_t i = 0; i < 20; i++) {
    temp_index[i] = tolower(XINABOX_INDEX[i]);
  }

  sprintf(topic_STEM, "xinabox/data/%s/%s", temp_index, "stemsat");
  sprintf(topic_COOKIE, "xinabox/data/%s/%s", temp_index, "cookiesat");
  sprintf(topic_TOAST, "xinabox/data/%s/%s", temp_index, "toastsat");

  lastSend = millis();
  lastServerCheck = millis();
}

void loop() {
  BLYNK_CONNECT();
  START_PHASE2();
  while (1) {
    DEMO_PHASE2();
    yield();
    BLYNK_LOOP();
  }
}








