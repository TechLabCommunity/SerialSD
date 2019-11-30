#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <Arduino.h>
#include <SdFat.h>
#include "constants.h"
#include "helpers/struct.h"
#include "helpers/utility.h"

struct Configuration {
  // EXAMPLE
  //   String euro_price_0, euro_price_1, euro_price_2;
  String det_name_1, det_name_2, det_name_3, det_name_4, det_name_5, det_name_6;
  int det_price_1, det_price_2, det_price_3, det_price_4, det_price_5,
      det_price_6;
  int pulse_x_l_1, pulse_x_l_2, pulse_x_l_3, pulse_x_l_4, pulse_x_l_5,
      pulse_x_l_6;
  int sec_x_l_1, sec_x_l_2, sec_x_l_3, sec_x_l_4, sec_x_l_5, sec_x_l_6;
  int det_max_l_1, det_max_l_2, det_max_l_3, det_max_l_4, det_max_l_5,
      det_max_l_6;
};

void get_configuration(Configuration *config, const SingleComposition &comp) {
  // EXAMPLE
  //   if (comp.first == "euro_price_0") {
  //     config->euro_price_0 = comp.second;
  //   } else if (comp.first == "euro_price_1") {
  //     config->euro_price_1 = comp.second;
  //   } else if (comp.first == "euro_price_2") {
  //     config->euro_price_2 = comp.second;

  if (comp.first == "name_1") {
    config->det_name_1 = comp.second;
  } else if (comp.first == "name_2") {
    config->det_name_2 = comp.second;
  } else if (comp.first == "name_3") {
    config->det_name_3 = comp.second;
  } else if (comp.first == "name_4") {
    config->det_name_4 = comp.second;
  } else if (comp.first == "name_5") {
    config->det_name_5 = comp.second;
  } else if (comp.first == "name_6") {
    config->det_name_6 = comp.second;
  }

  else if (comp.first == "price_1") {
    config->det_price_1 = comp.second.toInt();
  } else if (comp.first == "price_2") {
    config->det_price_2 = comp.second.toInt();
  } else if (comp.first == "price_3") {
    config->det_price_3 = comp.second.toInt();
  } else if (comp.first == "price_4") {
    config->det_price_4 = comp.second.toInt();
  } else if (comp.first == "price_5") {
    config->det_price_5 = comp.second.toInt();
  } else if (comp.first == "price_6") {
    config->det_price_6 = comp.second.toInt();
  }

  else if (comp.first == "pulses_1") {
    config->pulse_x_l_1 = comp.second.toInt();
  } else if (comp.first == "pulses_2") {
    config->pulse_x_l_2 = comp.second.toInt();
  } else if (comp.first == "pulses_3") {
    config->pulse_x_l_3 = comp.second.toInt();
  } else if (comp.first == "pulses_4") {
    config->pulse_x_l_4 = comp.second.toInt();
  } else if (comp.first == "pulses_5") {
    config->pulse_x_l_5 = comp.second.toInt();
  } else if (comp.first == "pulses_6") {
    config->pulse_x_l_6 = comp.second.toInt();
  }

  else if (comp.first == "timeout_1") {
    config->sec_x_l_1 = comp.second.toInt();
  } else if (comp.first == "timeout_2") {
    config->sec_x_l_2 = comp.second.toInt();
  } else if (comp.first == "timeout_3") {
    config->sec_x_l_3 = comp.second.toInt();
  } else if (comp.first == "timeout_4") {
    config->sec_x_l_4 = comp.second.toInt();
  } else if (comp.first == "timeout_5") {
    config->sec_x_l_5 = comp.second.toInt();
  } else if (comp.first == "timeout_6") {
    config->sec_x_l_6 = comp.second.toInt();
  }

  else if (comp.first == "max_L_1") {
    config->det_max_l_1 = comp.second.toInt();
  } else if (comp.first == "max_L_2") {
    config->det_max_l_2 = comp.second.toInt();
  } else if (comp.first == "max_L_3") {
    config->det_max_l_3 = comp.second.toInt();
  } else if (comp.first == "max_L_4") {
    config->det_max_l_4 = comp.second.toInt();
  } else if (comp.first == "max_L_5") {
    config->det_max_l_5 = comp.second.toInt();
  } else if (comp.first == "max_L_6") {
    config->det_max_l_6 = comp.second.toInt();
  }
}

bool get_value_from_key(String key, String *value,
                        Configuration &configuration) {
  key.trim();

  // EXAMPLE
  //   if (key == "euro_price_0") {
  //     (*value) = configuration.euro_price_0;
  //   } else if (key == "euro_price_1") {
  //     (*value) = configuration.euro_price_1;
  //   } else if (key == "euro_price_2") {
  //     (*value) = configuration.euro_price_2;
  //   }

  if (key == "name_1") {
    (*value) = configuration.det_name_1;
  } else if (key == "name_2") {
    (*value) = configuration.det_name_2;
  } else if (key == "name_3") {
    (*value) = configuration.det_name_3;
  } else if (key == "name_4") {
    (*value) = configuration.det_name_4;
  } else if (key == "name_5") {
    (*value) = configuration.det_name_5;
  } else if (key == "name_6") {
    (*value) = configuration.det_name_6;
  }

  else if (key == "price_1") {
    (*value) = configuration.det_price_1;
  } else if (key == "price_2") {
    (*value) = configuration.det_price_2;
  } else if (key == "price_3") {
    (*value) = configuration.det_price_3;
  } else if (key == "price_4") {
    (*value) = configuration.det_price_4;
  } else if (key == "price_5") {
    (*value) = configuration.det_price_5;
  } else if (key == "price_6") {
    (*value) = configuration.det_price_6;
  }

  else if (key == "pulses_1") {
    (*value) = configuration.pulse_x_l_1;
  } else if (key == "pulses_2") {
    (*value) = configuration.pulse_x_l_2;
  } else if (key == "pulses_3") {
    (*value) = configuration.pulse_x_l_3;
  } else if (key == "pulses_4") {
    (*value) = configuration.pulse_x_l_4;
  } else if (key == "pulses_5") {
    (*value) = configuration.pulse_x_l_5;
  } else if (key == "pulses_6") {
    (*value) = configuration.pulse_x_l_6;
  }

  else if (key == "timeout_1") {
    (*value) = configuration.sec_x_l_1;
  } else if (key == "timeout_2") {
    (*value) = configuration.sec_x_l_2;
  } else if (key == "timeout_3") {
    (*value) = configuration.sec_x_l_3;
  } else if (key == "timeout_4") {
    (*value) = configuration.sec_x_l_4;
  } else if (key == "timeout_5") {
    (*value) = configuration.sec_x_l_5;
  } else if (key == "timeout_6") {
    (*value) = configuration.sec_x_l_6;
  }

  else if (key == "max_L_1") {
    (*value) = configuration.det_max_l_1;
  } else if (key == "max_L_2") {
    (*value) = configuration.det_max_l_2;
  } else if (key == "max_L_3") {
    (*value) = configuration.det_max_l_3;
  } else if (key == "max_L_4") {
    (*value) = configuration.det_max_l_4;
  } else if (key == "max_L_5") {
    (*value) = configuration.det_max_l_5;
  } else if (key == "max_L_6") {
    (*value) = configuration.det_max_l_6;
  }

  else {
    (*value) = "";
    return false;
  }
  return true;
}

#endif