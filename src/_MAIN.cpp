#include <Arduino.h>

#include "cmd.h"
#include "rtc.h"
#include "config.h"

#include <Wire.h>

void wireReceive(int cnt)
{
  String cmd = "";
  while (Wire.available() >= 1)
  {
    auto c = Wire.read();
    cmd += (char)c;
  }
  processCmd(cmd);
}

void wireRequest()
{
#ifndef DISABLE_SERIAL_DEBUG
  Serial.println("REQ");
#endif
  Wire.write(wireResponse.c_str());
}

void setup()
{
#ifndef DISABLE_SERIAL_DEBUG
  Serial.begin(38400);
#endif

  Wire.begin(WIRE_ADDR);
  Wire.onReceive(wireReceive);
  Wire.onRequest(wireRequest);
}

String cmd = "";

void loop()
{
  maintenanceRTC();
}