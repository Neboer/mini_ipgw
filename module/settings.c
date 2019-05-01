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
        strcpy(settingFileString, setting->_IO_read_base);
//        fread(settingFileString, 100, settingFileSize + 1, setting);
        fclose(setting);
        return settingFileString;
    }
}

char *get_data(const char *option) {
    char *settingContent = get_settings(DEFAULT_SETTINGS_LOCATION);
//    char settingContent[] = "{\"default\":\"good\",\n\"what\":\"very\"}";
    if (!settingContent)
        return NULL;
    cJSON *filejson = cJSON_Parse(settingContent);
    const cJSON *field = cJSON_GetObjectItemCaseSensitive(filejson, option);
    if (field) {
        if (field->type == cJSON_String) {
            return field->valuestring;
        } else if (field->type == cJSON_Object) {
            return cJSON_Print(field);
        } else {
            fprintf(stderr, "error type %d", field->type);
            return NULL;
        }
    } else {
        fprintf(stderr, "no such field %s", option);
        return NULL;
    }
}