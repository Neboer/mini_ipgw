#include "openhelpfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HOME_LENGTH 100


void print_help_file(void) {
    char help_path[MAX_HOME_LENGTH];
    if (strlen(getenv("HOME")) > MAX_HOME_LENGTH - strlen("/.ipgw/helpfile.txt")) {
        fprintf(stderr, "Too long HOME path.\n");
        return;
    }
    strcpy(help_path, getenv("HOME"));
    strcat(help_path, "/.ipgw/helpfile.txt");
    FILE *helpFile = fopen(help_path, "r");
    if (!helpFile) {
        fprintf(stderr, "Help source file does not exist!\n");
        return;
    }
    fseek(helpFile, 0, SEEK_END);
    int helpFileSize = ftell(helpFile);
    fseek(helpFile, 0, SEEK_SET);
    char *content = malloc(helpFileSize);
    fread(content, helpFileSize + 1, 1, helpFile);
    printf("%s", content);
}