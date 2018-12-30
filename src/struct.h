#ifndef STRUCT_H
#define STRUCT_H
#include <Arduino.h>

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
struct Composition
{
    String first = "", second = "";
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

#endif