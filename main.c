#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX_UNPW_LENGTH 50

#include "module/settings.h"
#include "module/getinmemory.h"
#include "module/makerequest.h"
#include "module/parseresponse.h"
#include "module/openhelpfile.h"

int main(int argc, char *argv[]) {
    char username[MAX_UNPW_LENGTH], password[MAX_UNPW_LENGTH];
    short username_is_set = 0, password_is_set = 0, action = LOGIN;
    char option;// store the current parsing option character
    while ((option = getopt(argc, argv, "hu:p:o")) != -1) {
        switch (option) {
            case 'h':// show help page
            {
                print_help_file();
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
                fprintf(stderr, "error input.");
                return -1;
            }
        }
    }
    if (!username_is_set) {
        fprintf(stderr, "username not set");
        return -1;
    }
    if (!password_is_set) {
        fprintf(stderr, "password not set");
        return -1;
    }
    requests get_data = ipgw_action(action, username, password);
    switch (parse_ipgw_Result(get_data)) {
        case IPGW_USER_NOT_FOUND: {
            fprintf(stderr, "no user %s", username);
            return -1;
        }
        case IPGW_PASSWORD_ERROR: {
            fprintf(stderr, "password error");
            return -2;
        }
        case IPGW_NETWORK_CONNECTED:
            printf("connected to network");
            return 0;
    }
//    char file[5000];
//    FILE* fileee = fopen("/home/neboer/documents/ipgw-linux-c/response.html","r");
//    fread(file,5000,1,fileee);
//    char at[10];
//    sscanf(get_data.content,"%*3576c%s",at);
//    printf("%s",at);

//    char* what = strstr(file,"<p>E");
//    printf("%ld",what-file);
//    printf("%.50s",what);
//    printf("%d",get_data.code);
}