#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduino.h>
#include "constants.h"
#include <avr/io.h>
#include <avr/wdt.h>

#define Reset_AVR()        \
    wdt_enable(WDTO_30MS); \
    while (1)              \
    {                      \
    }

enum ErrorConfig
{
    FILE_NOT_FOUND = 0,
    JSON_PARSE_FAILED = 1,
    BEGIN_SD_FAILED = 2
};

void SYSTEM_ERROR(ErrorConfig err)
{
    String error_parse = "";
    switch (err)
    {
    case FILE_NOT_FOUND:
    {
        error_parse = SYSERR_FILE_NOT_FOUND;
    }
    break;
    case JSON_PARSE_FAILED:
    {
        error_parse = SYSERR_JSON_PARSE_FAILED;
    }
    break;
    case BEGIN_SD_FAILED:
    {
        error_parse = SYSERR_BEGIN_SD_FAILED;
    }
    break;
    default:
    {
        error_parse = SYSERR_UNKNOWN;
    }
    break;
    }
    uint8_t count_err = 0;
    while (count_err < COUNT_RESET)
    {
        Serial.println(error_parse);
        delay(1000);
        ++count_err;
    }
    Serial.println(COMMAND_RESET);
    Reset_AVR();
}

#endif