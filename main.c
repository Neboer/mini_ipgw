#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX_UNPW_LENGTH 50

#include "module/settings.h"
#include "module/getinmemory.h"
#include "module/makerequest.h"

int main(int argc, char *argv[]) {
    char username[MAX_UNPW_LENGTH], password[MAX_UNPW_LENGTH];
    short username_is_set = 0, password_is_set = 0, action = LOGIN;
    char option;// store the current parsing option character
    while ((option = getopt(argc, argv, "hu:p:o")) != -1) {
        switch (option) {
            case 'h':// show help page
            {
                return 0;
            }
            case 'u':// set username
            {
                strcpy(username, optarg);
                username_is_set = 1;
                break;
            }
            case 'p': {
                strcpy(password, optarg);
                password_is_set = 1;
                break;
            }
            case 'o': {
                action = LOGOUT;
                break;
            }
            default: {
                fprintf(stderr,"error input.");
                return -1;
            }
        }
    }
    if(!username_is_set) {fprintf(stderr,"username not set");
        return -1;}
    if(!password_is_set) {fprintf(stderr,"username not set");
        return -1;}
    requests get_data = ipgw_action(action, username, password);
}