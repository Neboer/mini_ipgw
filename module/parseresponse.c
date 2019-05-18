// parse the response of return data.
// E2531: User not found.(用户不存在)
#include "parseresponse.h"
#include <stdio.h>
#include <string.h>

int parse_ipgw_Result(requests req) {
    if (req.code == 503) return IPGW_SERVICE_UNAVAILABLE;
    else if (req.code == 200) {
        char errStr[10];
        sscanf(req.content, "%*3576c%s", errStr);
        if (strcmp(errStr, "E2531:") == 0) return IPGW_USER_NOT_FOUND;
        if (strcmp(errStr, "E2553:") == 0) return IPGW_PASSWORD_ERROR;
        if (strcmp(errStr, "p\">") == 0) return IPGW_NETWORK_CONNECTED;
        else {
            fprintf(stderr, "parse ipgw response error!");
            return -1;
        }
    } else {
        fprintf(stderr, "error get code %d", req.code);
        return -2;
    }
}