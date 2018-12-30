#include <ArduinoJson.h>
#include <SD.h>
#include <SPI.h>
#include "constants.h"
#include "syserror.h"
#include "utility.h"
#include "struct.h"

Configuration *configuration;

Configuration *loadConfiguration();
String wait_request_serial();
SerialConfiguration *ser_conf = new SerialConfiguration();
Configuration *loadConfiguration();

bool get_config_value(String key, String *value);
SerialResponse handle(SerialRequest ser_req);
SerialRequest unserialize_request(String &s);

void setup()
{
  Serial.begin(9600);
  Serial.flush();
  Serial.println(COMMAND_START);
  while (!SD.begin(CHIP_SELECT))
  {
    ErrorConfig err = BEGIN_SD_FAILED;
    SYSTEM_ERROR(err);
  }
  ser_conf->message_timeout = DEFAULT_MESSAGE_TIMEOUT;
  configuration = loadConfiguration();
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
      response.result = RESULT_KEY_NOT_FOUND;
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
      response.result = RESULT_IMPOSSIBLE_WRITE;
      return response;
    }
    response.type_response = OK;
    response.result = RESULT_WRITTEN;
  }
  break;
  case (UNKNOWN):
  {
    response.type_response = ERROR;
    response.result = RESULT_BAD_REQUEST;
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
  if (compose[0].equalsIgnoreCase(PREFIX_GET))
  {
    req.type_req = GET_CONFIGURATION;
    req.value = compose[1];
  }
  else if (compose[0].equalsIgnoreCase(PREFIX_LOG))
  {
    req.type_req = LOG_WRITE;
    req.value = compose[1];
  }
  else if (compose[0].equalsIgnoreCase(PREFIX_ACK))
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
  String type_word = "";
  switch (resp.type_response)
  {
  case OK:
  {
    type_word = PREFIX_RESPONSE_OK;
  }
  break;
  case ERROR:
  {
    type_word = PREFIX_RESPONSE_ERR;
  }
  break;
  }
  delay(80);
  Serial.println(String(type_word) + ":" + resp.result);
  Serial.flush();
#ifdef SHOW_MEM_FREE
  Serial.println("Free RAM : " + String(freeRam()));
#endif
}

Configuration *loadConfiguration()
{
  Configuration *config = new Configuration();
  File file = SD.open(CONFIG_FILE);
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

bool get_config_value(String key, String *value)
{
  key.trim();
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