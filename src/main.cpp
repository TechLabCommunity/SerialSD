#include <SdFat.h>
#include <SPI.h>
#include "constants.h"
#include "syserror.h"
#include "utility.h"
#include "configuration.h"
#include "struct.h"

Configuration *configuration;
SdFat sd;

void get_configuration(Configuration *config, const Composition &comp);
Configuration *load_configuration();
String wait_request_serial();
SerialConfiguration *ser_conf = new SerialConfiguration();
Configuration *load_configuration();

bool get_config_value(String, String *);
SerialResponse handle(SerialRequest);
SerialRequest unserialize_request(String &);
Composition parse_format(String s);

void setup()
{
  Serial.begin(9600);
  Serial.flush();
  ser_conf->message_timeout = DEFAULT_MESSAGE_TIMEOUT;
  while (!sd.begin(CHIP_SELECT, SPI_HALF_SPEED))
  {
    ErrorConfig err = BEGIN_SD_FAILED;
    SYSTEM_ERROR(err);
  }
  if (!sd.exists(LOG_FILE))
  {
    SdFile file;
    file.open(LOG_FILE, O_CREAT);
    file.close();
  }
  configuration = load_configuration();
  Serial.println(COMMAND_START);
}

bool write_log(String s)
{
  s.trim();
  SdFile log_file;
  log_file.open(LOG_FILE, O_CREAT | O_WRITE | O_AT_END);
  if (log_file.dirSize() >= MAX_SIZE_LOG)
  {
    log_file.close();
    log_file.remove();
    log_file.open(LOG_FILE, O_CREAT | O_WRITE | O_AT_END);
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
    if (!get_from_configuration(ser_req.value, &value, *configuration))
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
  if (s.length() == 0 || how_many_occur_char(s, DELIMITER) == 0)
  {
    req.type_req = UNKNOWN;
    return req;
  }
  Composition comp = parse_format(s);
  if (comp.second.length() == 0)
  {
    req.type_req = UNKNOWN;
  }
  if (comp.first.equalsIgnoreCase(PREFIX_GET))
  {
    req.type_req = GET_CONFIGURATION;
    req.value = comp.second;
  }
  else if (comp.first.equalsIgnoreCase(PREFIX_LOG))
  {
    req.type_req = LOG_WRITE;
    req.value = comp.second;
  }
  else if (comp.first.equalsIgnoreCase(PREFIX_ACK))
  {
    req.type_req = ACK;
    req.value = comp.second;
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

Configuration *load_configuration()
{
  Configuration *config = new Configuration();
  SdFile conf_file;
  conf_file.open(CONFIG_FILE, O_READ);
  char line[MAX_LINE_SIZE];
  uint32_t n;
  while ((n = conf_file.fgets(line, sizeof(line))) > 0)
  {
    String line_s = String(line);
    line_s.trim();
    Composition comp = parse_format(line_s);
    get_configuration(config, comp);
  }
  conf_file.close();
  return config;
}