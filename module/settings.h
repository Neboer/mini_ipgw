//The file aimed at make and parse settings.json file
#ifndef IPGW_SETTINGS_H
#define IPGW_SETTINGS_H

char *getPostData(int options);

void *getSettingsData(const char *options);// Notice: if string will return char*, etc...

#endif //IPGW_SETTINGS_H
