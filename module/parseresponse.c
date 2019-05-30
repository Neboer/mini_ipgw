// parse the response of return data.
// E2531: User not found.(用户不存在)
// 您似乎未曾连接到网络...
// 注销失败：Password is error.
// 网络已断开
#include "parseresponse.h"
#include "makerequest.h"
#include "settings.h"
#include <stdio.h>
#include <string.h>

struct compare_instant {
    char *pattern, *user_not_found, *password_error, *already_online, *connected;
};

struct compare_instant makeCompareInstant() {// TODO: wait for get multi setting.
    struct compare_instant instant;
    instant.pattern = getSettingsObject(1, "match_pattern");
    instant.user_not_found = getSettingsObject(2, "compare_string", "user not found");
    instant.password_error = getSettingsObject(2, "compare_string", "password error");
    instant.already_online = getSettingsObject(2, "compare_string", "already online");
    instant.connected = getSettingsObject(2, "compare_string", "connected");
    return instant;
}

int parse_ipgw_Result(requests req) {
    if (req.type == IPGW_REQUEST_LOGIN) {
        if (req.code == 503) return IPGW_SERVICE_UNAVAILABLE;
        else if (req.code == 200) {
            char errStr[10];
            struct compare_instant instant = makeCompareInstant();
            if (!instant.pattern) return -1;
            sscanf(req.content, instant.pattern, errStr);// TODO: potential over-copy leak.
            if (strcmp(errStr, instant.user_not_found) == 0) return IPGW_USER_NOT_FOUND;
            if (strcmp(errStr, instant.password_error) == 0) return IPGW_PASSWORD_ERROR;
            if (strcmp(errStr, instant.already_online) == 0) return IPGW_ALREADY_ONLINE;
            if (strcmp(errStr, instant.connected) == 0) return IPGW_NETWORK_CONNECTED;
            else {
                fprintf(stderr, "parse ipgw response error!Error comparision string:\n%s\n", errStr);
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
