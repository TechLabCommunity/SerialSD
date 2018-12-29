#include <ArduinoJson.h>
#include "global.h"
#include <SD.h>
#include <SPI.h>
#define CHIP_SELECT 4
#define BUFFER_JSON 256
#define DELIMITER ':'
const char *filename = "CONFIG.TXT";
Configuration *configuration;
JsonObject *root;

Configuration *loadConfiguration()
{
  Configuration *config = new Configuration();
  File file = SD.open(filename);
  StaticJsonBuffer<BUFFER_JSON> jsonBuffer;
  JsonObject &root = jsonBuffer.parseObject(file);
  if (!root.success())
  {
    SYSTEM_ERROR(JSON_PARSE_FAILED);
  }
  config->euro_price = String(root["euro_price"].as<String>());
  config->version = String(root["version"].as<String>());
  file.close();
  return config;
}

void setup()
{
  Serial.begin(9600);
  Serial.flush();
  while (!SD.begin(CHIP_SELECT))
  {
    ErrorConfig err = BEGIN_SD_FAILED;
    SYSTEM_ERROR(err);
  }
  configuration = loadConfiguration();
  Serial.println("START");
}

String &waitRequestSerial();

void loop()
{
  String &s = waitRequestSerial();
  delay(80);
  Serial.println(s);
  Serial.flush();
}

String &waitRequestSerial()
{
  String *request = new String();
  bool is_finish = false;
  Serial.println("Wait serial...");
  while (!is_finish)
  {
    if (Serial.available())
    {
      (*request) += (char)Serial.read();
    }
    is_finish = request->length() > 0 && (*request)[request->length() - 1] == '\n';
  }
  return *request;
}