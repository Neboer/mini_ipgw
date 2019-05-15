// main function, aimed at receive & pass flags
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <iostream>

extern "C" {
#include "module/settings.h"
#include "module/getinmemory.h"
#include "module/makerequest.h"
}

using namespace std;

string username = string(), password;
bool username_is_set = false, password_is_set = false, action = LOGIN;

void replace_words(string &words){
    words.replace(words.find("${username}"), 11, username);
    words.replace(words.find("${password}"), 11, password);
}

int main(int argc, char *argv[]) {// programme entrance
    char option;// getopt() currently handle option
    const char help_file_location[] = "/home/neboer/documents/ipgw-linux-c/src/helpfile.txt";
    while ((option = getopt(argc, argv, "hu:p:o")) != -1) {
        switch (option) {
            case 'h':// show help page
            {
                ifstream help_file(help_file_location);
                ostringstream help;
                if (!help_file.is_open()) {
                    cout << "help file error.";
                    return -1;
                }
                help << help_file.rdbuf();
                cout << help.str();
                help_file.close();
                return 0;
            }
            case 'u':// set username
            {
                username = string(optarg);
                if (username.empty()) {
                    cerr << "username cannot be empty";
                    return -1;
                } else {
                    username_is_set = true;
                }
                break;
            }
            case 'p': {
                password = string(optarg);
                if (password.empty()) {
                    cerr << "password cannot be empty, please check.";
                    return -1;
                } else {
                    password_is_set = true;
                }
                break;
            }
            case 'o': {
                action = LOGOUT;
                break;
            }
            default: {
                cerr << "error input.";
            }
        }
    }
    if (!username_is_set) {
        cerr << "must input username";
        return -1;
    }
    if (!password_is_set) {
        cerr << "must input password";
        return -1;
    }
    ipgw_action(action,username,password);
}