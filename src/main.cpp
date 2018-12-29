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

String &wait_request_serial();

Configuration *loadConfiguration();

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

SerialRequest &unserialize_request(String &s)
{
  SerialRequest *req = new SerialRequest();
  if (s.length() == 0)
  {
    return *req;
  }
  String compose[2];
  compose[0] = compose[1] = "";
  uint8_t i = 0;
  uint8_t part = 0;
  while (i < s.length() && s[i] != '\n')
  {
    if (s[i] == DELIMITER)
    {
      ++part;
    }
    else
    {
      compose[part] += s[i];
    }
    i++;
  }
  if (compose[0] == "GET")
  {
    req->type_req = GET_CONFIGURATION;
  }
  else if (compose[0] == "LOG")
  {
    req->type_req = LOG_WRITE;
  }
  else
  {
    req->type_req = UNKNOWN;
  }
  req->value = compose[2];
  return *req;
}

void loop()
{
  String &s = wait_request_serial();
  SerialRequest &req = unserialize_request(s);
  delay(80);
  Serial.println(req.type_req);
  Serial.println(req.value);
  Serial.flush();
}

String &wait_request_serial()
{
  String *request = new String();
  bool is_finish = false;
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