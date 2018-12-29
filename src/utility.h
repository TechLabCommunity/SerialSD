#ifndef UTILITY_H
#define UTILITY_H
#include <Arduino.h>

int how_many_occur_char(String &s, char c)
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

#endif