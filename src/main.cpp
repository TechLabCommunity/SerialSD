#include <ArduinoJson.h>
#include "global.h"
#include "utility.h"
#include "struct.h"
#include <SD.h>
#include <SPI.h>
#define CHIP_SELECT 4
#define BUFFER_JSON 256
#define DEFAULT_MESSAGE_TIMEOUT "ERR:MAX_TIMEOUT_REACH"
#define DELIMITER ':'
#define MAX_SIZE_LOG 7000000000
#define CONFIG_FILE "CONFIG.TXT"
#define LOG_FILE "LOG.TXT"

const char *filename = CONFIG_FILE;
volatile bool busy_ping = false;
Configuration *configuration;
JsonObject *root;

String wait_request_serial();
SerialConfiguration *ser_conf = new SerialConfiguration();
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
  ser_conf->message_timeout = "ERR:MAX_TIMEOUT_REACH";
  configuration = loadConfiguration();
  Serial.println("START");
}

bool get_config_value(String key, String *value)
{
  if (key == "euro_price")
  {
    (*value) = configuration->euro_price;
  }
  else if (key == "version")
  {
    (*value) = configuration->version;
  }
  else
  {
    (*value) = String("");
    return false;
  }
  return true;
}

bool write_log(String s)
{
  s.trim();
  File log_file = SD.open(LOG_FILE, FILE_WRITE);
  if (log_file.size() >= MAX_SIZE_LOG)
  {
    log_file.close();
    SD.remove(LOG_FILE);
    log_file = SD.open(LOG_FILE, FILE_WRITE);
  }
  log_file.println(s);
  log_file.close();
  return true;
}

SerialResponse handle(SerialRequest ser_req)
{
  SerialResponse response;
  switch (ser_req.type_req)
  {
  case (GET_CONFIGURATION):
  {
    String value;
    if (!get_config_value(ser_req.value, &value))
    {
      response.type_response = ERROR;
      response.result = "KEY_NOT_FOUND";
      return response;
    }
    response.type_response = OK;
    response.result = value;
  }
  break;
  case (LOG_WRITE):
  {
    if (!write_log(ser_req.value))
    {
      response.type_response = ERROR;
      response.result = "IMPOSSIBLE_WRITE";
      return response;
    }
    response.type_response = OK;
    response.result = "WRITTEN";
  }
  break;
  case (UNKNOWN):
  {
    response.type_response = ERROR;
    response.result = "BAD_REQUEST";
  }
  break;
  case (ACK):
  {
    response.type_response = OK;
    response.result = ser_req.value;
  }
  break;
  }
  return response;
}

SerialRequest unserialize_request(String &s)
{
  SerialRequest req;
  s.trim();
  if (s.length() == 0 || how_many_occur_char(s, DELIMITER) == 0)
  {
    req.type_req = UNKNOWN;
    return req;
  }
  String compose[2];
  compose[0] = compose[1] = "";
  uint8_t i = 0;
  uint8_t part = 0;
  bool is_passed_term = false;
  while (i < s.length() && s[i] != '\n')
  {
    if (s[i] == DELIMITER && !is_passed_term)
    {
      ++part;
      is_passed_term = true;
    }
    else
    {
      compose[part] += s[i];
    }
    i++;
  }
  compose[1].trim();
  if (compose[1].length() == 0)
  {
    req.type_req = UNKNOWN;
  }
  if (compose[0].equalsIgnoreCase("GET"))
  {
    req.type_req = GET_CONFIGURATION;
    req.value = compose[1];
  }
  else if (compose[0].equalsIgnoreCase("LOG"))
  {
    req.type_req = LOG_WRITE;
    req.value = compose[1];
  }
  else if (compose[0].equalsIgnoreCase("ACK"))
  {
    req.type_req = ACK;
    req.value = compose[1];
  }
  else
  {
    req.type_req = UNKNOWN;
  }
  return req;
}

void loop()
{
  String s = wait_request_serial(*ser_conf);
  SerialRequest req = unserialize_request(s);
  SerialResponse resp = handle(req);
  delay(80);
  Serial.println(String(resp.type_response) + ":" + resp.result);
  Serial.flush();
#ifdef SHOW_MEM_FREE
  Serial.println("Free RAM : " + String(freeRam()));
#endif
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