//The file aimed at make and parse settings.json file
#ifndef IPGW_SETTINGS_H
#define IPGW_SETTINGS_H


#define DEFAULT_SETTINGS_LOCATION "/home/neboer/documents/ipgw-linux-c/settings.json"


char *getPostData(int options);

void *getSettingsData(const char *options);// Notice: if string will return char*, etc...

#endif //IPGW_SETTINGS_H
