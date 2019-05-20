#include "openhelpfile.h"
#include <stdio.h>
#include <stdlib.h>

void print_help_file(void) {
    const char help_file_location[] = "/home/neboer/documents/ipgw-linux-c/src/helpfile.txt";
    FILE *helpFile = fopen(help_file_location, "r");
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