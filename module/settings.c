//The file aimed at make and parse settings.json file
#include "settings.h"
#include "makerequest.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#define MAX_HOME_LENGTH 100
#define MAX_ARRAY_INDEX 100 //distinguish pass item is array index or string.
#define MAX_ARG_NUMBER 10 // the max number of passed args.

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
    return parsed_settings;
}

// a function aimed at get settings
union arg {
    long act_val;
    short int_arg;
    char *str_arg;
};

short arg_is_index(union arg arg) {
    if (arg.act_val < 0 || arg.act_val > MAX_ARRAY_INDEX) {//if passed arg is string not index
        return 0;
    } else//else passed arg is index.
    {
        return 1;
    }
}

void *getSettingsObject(int argc, ...)// powerful function. Get data and return the deep data in object.
{
    if (argc > MAX_ARG_NUMBER) {
        fprintf(stderr, "passed too much arguments.");
        return NULL;
    }
    va_list arglist;
    va_start(arglist, argc);

    union arg current_arg, history[MAX_ARG_NUMBER];
    cJSON *walker = get_parsed_settings();
    for (int i = 0; i < argc; i++) {
        current_arg.act_val = va_arg(arglist, long);// use actual value to assign.
        if (arg_is_index(current_arg)) {
            walker = cJSON_GetArrayItem(walker, current_arg.int_arg);
        } else {
            walker = cJSON_GetObjectItemCaseSensitive(walker, current_arg.str_arg);
        }
        history[i] = current_arg;// store current argument to memory
        if (!walker) {
            fprintf(stderr, "error get ");
            for (int j = 0; j <= i; j++) {
                if (arg_is_index(history[j])) {
                    fprintf(stderr, "[%d]", history[j].int_arg);
                } else {
                    fprintf(stderr, ".%s", history[j].str_arg);
                }
            }
            fprintf(stderr, "\n");
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