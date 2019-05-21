//The file aimed at make and parse settings.json file
#include "settings.h"
#include "makerequest.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cjson/cJSON.h>


char *get_settings(const char *input_loc) {
    errno = 0;
    FILE *setting = fopen(input_loc, "r");
    char *settingFileString;
    if (errno) {
        fprintf(stderr, "cannot open %s: %s\n", input_loc, strerror(errno));
        return NULL;
    } else {
        fseek(setting, 0, SEEK_END);// Try to use ANSI C standard function to get the size of setting file.
        const int settingFileSize = ftell(setting);
        settingFileString = malloc(settingFileSize);
        fseek(setting, 0, SEEK_SET);
        fread(settingFileString, settingFileSize + 1, 1, setting);
        fclose(setting);
        return settingFileString;
    }
}

cJSON *get_parsed_settings() {
    char *setting_string = get_settings(strcat(getenv("HOME"), "/.ipgw/settings.json"));
    if (!setting_string) return NULL;
    return cJSON_Parse(setting_string);//TODO: add error-shooting methods
}

void *getSettingsData(const char *options) {// Notice: if string will return char*, etc...
    cJSON *setting_json = get_parsed_settings();
    if (!setting_json) return NULL;
    cJSON *content_value = cJSON_GetObjectItemCaseSensitive(setting_json, options);
    if (!content_value) {
        fprintf(stderr, "error get data %s", options);
        return NULL;
    }
    if (cJSON_IsNumber(content_value))return &content_value->valueint;
    else if (cJSON_IsString(content_value))return content_value->valuestring;
    else return content_value;
}

char *getPostData(int options) {
    cJSON *whole_post_data = (cJSON *) getSettingsData("postdata");
    cJSON *log_string;
    if (options == IPGW_REQUEST_LOGIN) {
        log_string = cJSON_GetObjectItemCaseSensitive(whole_post_data, "login");
    } else {
        log_string = cJSON_GetObjectItemCaseSensitive(whole_post_data, "logout");
    }
    if (!log_string || !cJSON_IsString(log_string)) {
        fprintf(stderr, "error read post data\n");
        return NULL;
    }
    return log_string->valuestring;
}