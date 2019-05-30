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
    short username_is_set = 0, password_is_set = 0, action = IPGW_REQUEST_LOGIN, test = 0;
    int option;// store the current parsing option character
    if (argc == 1) {
        print_help_file();
        return 0;
    }
    while ((option = getopt(argc, argv, "hu:p:ovt")) != -1 && option != 255) {
        switch (option) {
            case 'h':// show help page
            {
                print_help_file();
                return 0;
            }
            case 'u':// set username
            {
                if (strlen(optarg) > MAX_UNPW_LENGTH - 1) {
                    printf("too long input");
                    return -1;
                }
                strcpy(username, optarg);
                username_is_set = 1;
                break;
            }
            case 'p': {
                if (strlen(optarg) > MAX_UNPW_LENGTH - 1) {
                    printf("too long input");
                    return -1;
                }
                strcpy(password, optarg);
                password_is_set = 1;
                break;
            }
            case 'o': {
                action = IPGW_REQUEST_LOGOUT;
                break;
            }
            case 'v': {
                printf("v1.0\n");
                return 0;
            }
            case 't': {
                test = 1;// test mode enable
                break;
            }
            default: {
                fprintf(stderr, "error input %c\n", option);
                return -1;
            }
        }
    }
    if (!username_is_set) {
        fprintf(stderr, "username not set\n");
        return -1;
    }
    if (password_is_set) {
        fprintf(stderr, "recommend you not use -p, input password in lint area.\n");
    } else {
        char *pass = getpass("password:");
        if (!pass) {
            fprintf(stderr, "password cannot be empty!");
            return -1;
        }
        strcpy(password, pass);
    }
    requests get_data = ipgw_action(action, username, password);
    if (test) {
        printf("%s", get_data.content);
//        printf("%ld", strstr(get_data.content, "<p>E") - get_data.content);
        return 0;
    }
    switch (parse_ipgw_Result(get_data)) {
        case IPGW_USER_NOT_FOUND: {
            fprintf(stderr, "no user %s\n", username);
            return -1;
        }
        case IPGW_PASSWORD_ERROR: {
            fprintf(stderr, "password error\n");
            return -2;
        }
        case IPGW_NETWORK_CONNECTED: {
            printf("connected to network\n");
            return 0;
        }
        case IPGW_NETWORK_DISCONNECTED: {
            return 0;
        }
        case IPGW_ALREADY_ONLINE: {
            printf("correct, but user already online.\n");
        }
        default: {
            return 0;
        }
    }
}
