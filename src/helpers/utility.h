#ifndef UTILITY_H
#define UTILITY_H
#include <Arduino.h>

struct SingleComposition
{
    String first = "", second = "";
};

struct SerialConfiguration
{
    char terminator = '\n';
    String message_timeout = DEFAULT_MESSAGE_TIMEOUT;
    uint64_t timeout_buffer = 3000;
    uint16_t max_buffer_size = 100;
};

uint16_t how_many_occur_char(String &s, char c)
{
    if (s.length() == 0)
        return 0;
    int count = 0;
    for (uint8_t i = 0; i < s.length(); i++)
    {
        count += (s[i] == c);
    }
    return count;
}

uint32_t freeRam()
{
    extern uint32_t __heap_start, *__brkval;
    int v;
    return (uint32_t)&v - (__brkval == 0 ? (uint32_t)&__heap_start : (uint32_t)__brkval);
}

String wait_request_serial(SerialConfiguration &ser_conf)
{
    String request = "";
    bool start_timer = false;
    uint64_t timer_ms = 0;
    Serial.flush();
    while (request.length() == 0 || request[request.length() - 1] != ser_conf.terminator)
    {
        if (start_timer)
        {
            if (millis() - timer_ms >= ser_conf.timeout_buffer)
            {
                timer_ms = 0;
                request = "";
                start_timer = false;
                if (ser_conf.message_timeout.length() > 0)
                    Serial.println(ser_conf.message_timeout);
            }
        }
        else if (request.length() == 1)
        {
            timer_ms = millis();
            start_timer = true;
        }
        if (Serial.available())
        {
            request += (char)Serial.read();
        }
        if (request.length() > 0)
        {
            if (request.length() > ser_conf.max_buffer_size)
            {
                request += ser_conf.terminator; //Truncate request.
            }
        }
    }
    Serial.flush();
    return String(request);
}

SingleComposition parse_format(String s)
{
    SingleComposition comp;
    s.trim();
    comp.first = comp.second = "";
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
            switch (part)
            {
            case 0:
                comp.first += s[i];
                break;
            case 1:
                comp.second += s[i];
                break;
            }
        }
        i++;
    }
    comp.first.trim();
    comp.second.trim();
    return comp;
}

#endif