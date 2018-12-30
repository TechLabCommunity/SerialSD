#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <SdFat.h>
#include <Arduino.h>
#include "struct.h"
#include "utility.h"
#include "constants.h"

Composition parse_format(String s);

struct Configuration
{
    String euro_price_0, euro_price_1, euro_price_2;
};

void get_configuration(Configuration *config, const Composition &comp)
{
    if (comp.first == "euro_price_0")
    {
        config->euro_price_0 = comp.second;
    }
    else if (comp.first == "euro_price_1")
    {
        config->euro_price_1 = comp.second;
    }
    else if (comp.first == "euro_price_2")
    {
        config->euro_price_2 = comp.second;
    }
}

bool get_from_configuration(String key, String *value, Configuration &configuration)
{
    key.trim();
    if (key == "euro_price_0")
    {
        (*value) = configuration.euro_price_0;
    }
    else if (key == "euro_price_1")
    {
        (*value) = configuration.euro_price_1;
    }
    else if (key == "euro_price_2")
    {
        (*value) = configuration.euro_price_2;
    }
    else
    {
        (*value) = "";
        return false;
    }
    return true;
}

#endif