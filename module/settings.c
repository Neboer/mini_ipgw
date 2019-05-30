//The file aimed at make and parse settings.json file
#include "settings.h"
#include "makerequest.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cjson/cJSON.h>
#include <stdarg.h>

#define MAX_HOME_LENGTH 100

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
    char setting_path[MAX_HOME_LENGTH];
    if (strlen(getenv("HOME")) > MAX_HOME_LENGTH - strlen("/.ipgw/settings.json")) {
        fprintf(stderr, "Too long HOME path.\n");
        return NULL;
    }
    strcpy(setting_path, getenv("HOME"));
    strcat(setting_path, "/.ipgw/settings.json");
    char *setting_string = get_settings(setting_path);
    if (!setting_string) return NULL;
    return cJSON_Parse(setting_string);//TODO: add error-shooting methods
}

void *get_settings_item(cJSON *json, int argc, ...)// powerful function. Get data and return the deep data in object.
{
    va_list arglist;
    va_start(arglist, argc);
    char *a;
    cJSON *walker = json;
    for (int i = 0; i < argc; i++) {
        a = va_arg(arglist, char *);
        walker = cJSON_GetObjectItemCaseSensitive(walker, a);
        if (!walker) {
            fprintf(stderr, "error get %s\n", a);
            return NULL;
        }
    }
    va_end(arglist);
    if (cJSON_IsString(walker)) {
        return (char *) walker->valuestring;
    } else if (cJSON_IsNumber(walker)) {
        return &(walker->valueint);
    } else if (cJSON_IsObject(walker)) {
        return walker;
    }
    return NULL;
}

void *getSettingsData(const char *options) {// Notice: if string will return char*, etc...
    cJSON *setting_json = get_parsed_settings();
    if (!setting_json) return NULL;
    cJSON *content_value = cJSON_GetObjectItemCaseSensitive(setting_json, options);
    if (!content_value) {
        fprintf(stderr, "error get data %s\n", options);
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