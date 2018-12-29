#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduino.h>
#include <avr/io.h>
#include <avr/wdt.h>
#define Reset_AVR()        \
    wdt_enable(WDTO_30MS); \
    while (1)              \
    {                      \
    }
#define COUNT_RESET 10

enum ErrorConfig
{
    FILE_NOT_FOUND = 0,
    JSON_PARSE_FAILED = 1,
    BEGIN_SD_FAILED = 2
};

enum TypeSerialRequest
{
    GET_CONFIGURATION = 0,
    LOG_WRITE = 1,
    UNKNOWN = 2,
    ACK = 3
};

enum TypeSerialResponse
{
    OK = 0,
    ERROR = 1
};

struct Configuration
{
    String version, euro_price;
};

struct SerialRequest
{
    TypeSerialRequest type_req = UNKNOWN;
    String value = "";
};

struct SerialResponse
{
    TypeSerialResponse type_response = OK;
    String result = "";
};

void SYSTEM_ERROR(ErrorConfig err)
{
    String error_parse = "XXX";
    switch (err)
    {
    case FILE_NOT_FOUND:
    {
        error_parse = "FILE_NOT_FOUND";
    }
    break;
    case JSON_PARSE_FAILED:
    {
        error_parse = "JSON_PARSE_FAILED";
    }
    break;
    case BEGIN_SD_FAILED:
    {
        error_parse = "BEGIN_SD_FAILED";
    }
    break;
    default:
    {
        error_parse = "UNKNOWN";
    }
    break;
    }
    uint8_t count_err = 0;
    while (count_err < COUNT_RESET)
    {
        Serial.println("SYSERR:" + error_parse);
        delay(1000);
        ++count_err;
    }
    Serial.println("RESET");
    Reset_AVR();
}

int freeRam()
{
    extern int __heap_start, *__brkval;
    int v;
    return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}

#endif