//The file aimed at make and parse settings.json file
#include "settings.h"
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
//        strcpy(settingFileString, setting->_IO_read_base);
//        fread(settingFileString, 100, settingFileSize + 1, setting);
        fclose(setting);
        return settingFileString;
    }
}

cJSON *get_parsed_settings() {
    char *setting_string = get_settings(DEFAULT_SETTINGS_LOCATION);
    if (!setting_string) return NULL;
    return cJSON_Parse(setting_string);//TODO: add error-shooting methods
}

char *getRawPostDataString(int activity) {
    cJSON *post_data_json = cJSON_GetObjectItemCaseSensitive(get_parsed_settings(), "postdata");
    cJSON *new_data_json = cJSON_CreateObject();
    if (post_data_json == NULL) return NULL;
    for (cJSON *walker = post_data_json->child; walker; walker = walker->next) {
        if (cJSON_IsArray(walker)) {
            cJSON *item = cJSON_GetArrayItem(walker, activity);
            if (cJSON_IsString(item)) {
                cJSON_AddStringToObject(new_data_json, walker->string, item->valuestring);
            } else {
                fprintf(stderr, "POST: error praising %s", walker->string);
                return NULL;
            }
        } else if (cJSON_IsString(walker)) {
            cJSON_AddStringToObject(new_data_json, walker->string, walker->valuestring);
        } else if (cJSON_IsNumber(walker)) {
            cJSON_AddNumberToObject(new_data_json, walker->string, walker->valuedouble);
        } else {
            fprintf(stderr, "POST: cannot deal with object %s", walker->string);
            return NULL;
        }
    }
    return cJSON_PrintUnformatted(new_data_json);
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
    else return cJSON_Print(content_value);
}