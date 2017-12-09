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


void runBlynk(void){
  Blynk.run();
}

void task_BlynkUpdate(void){
  BLYNK_PHASE2();
}

BLYNK_WRITE(V0){
  V0_State = param.asInt();
}

BLYNK_WRITE(V1){
  V1_State = param.asInt();
}

BLYNK_WRITE(V2){
  V2_State = param.asInt();
}

BLYNK_WRITE(V3){
  V3_State = param.asInt();
}


