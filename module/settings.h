//The file aimed at make and parse settings.json file
#ifndef IPGW_SETTINGS_H
#define IPGW_SETTINGS_H

#include <cjson/cJSON.h>

void *getSettingsObject(int argc, ...);// powerful function. Get data and return the deep data in object.
#endif //IPGW_SETTINGS_H
