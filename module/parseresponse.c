// parse the response of return data.
// E2531: User not found.(用户不存在)
#include "parseresponse.h"
#include <stdio.h>
#include <string.h>

void find_result_code_string(char *response, char *result) {
    char *index = strstr(response, "<p>E");
    if (!index) return;
    strncpy(result, index + 3, 5);
}

