// parse the response of return data.
// E2531: User not found.(用户不存在)
// 您似乎未曾连接到网络...
// 注销失败：Password is error.
// 网络已断开
#include "parseresponse.h"
#include "makerequest.h"
#include <stdio.h>
#include <string.h>

int parse_ipgw_Result(requests req) {
    if (req.type == IPGW_REQUEST_LOGIN) {
        if (req.code == 503) return IPGW_SERVICE_UNAVAILABLE;
        else if (req.code == 200) {
            char errStr[10];
            sscanf(req.content, "%*3576c%s", errStr);
            if (strcmp(errStr, "E2531:") == 0) return IPGW_USER_NOT_FOUND;
            if (strcmp(errStr, "E2553:") == 0) return IPGW_PASSWORD_ERROR;
            if (strcmp(errStr, "op\">") == 0) return IPGW_NETWORK_CONNECTED;
            else {
                fprintf(stderr, "parse ipgw response error!Error code:\n%s", errStr);
                return -1;
            }
        } else {
            fprintf(stderr, "error get code %d", req.code);
            return -2;
        }
    } else if (req.type == IPGW_REQUEST_LOGOUT) {
        printf("%s\n", req.content);
        if (strcmp(req.content, "网络已断开") == 0) {
            return IPGW_NETWORK_DISCONNECTED;
        }
        return IPGW_NETWORK_DISCONNECTED_ERROR;
    } else {
        return -1;
    }
}