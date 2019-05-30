//The file aimed at make and parse settings.json file
#include "settings.h"
#include "makerequest.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
    cJSON *parsed_settings = cJSON_Parse(setting_string);
    if (!parsed_settings) {
        fprintf(stderr, "Parse settings file ERROR!");
        return NULL;
    }
    return parsed_settings;//TODO: add error-shooting methods
}

void *getSettingsObject(int argc, ...)// powerful function. Get data and return the deep data in object.
{
    va_list arglist;
    va_start(arglist, argc);
    char *current_arg;
    cJSON *walker = get_parsed_settings();
    for (int i = 0; i < argc; i++) {
        current_arg = va_arg(arglist, char *);
        walker = cJSON_GetObjectItemCaseSensitive(walker, current_arg);
        if (!walker) {
            fprintf(stderr, "error get %s\n", current_arg);
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