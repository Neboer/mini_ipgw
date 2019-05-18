//
#ifndef IPGW_PARSERESPONSE_H
#define IPGW_PARSERESPONSE_H

#include "getinmemory.h"

#define IPGW_NETWORK_CONNECTED 0
#define IPGW_USER_NOT_FOUND 2531
#define IPGW_PASSWORD_ERROR 2553
#define IPGW_SERVICE_UNAVAILABLE 503


int parse_ipgw_Result(requests req);

#endif //IPGW_PARSERESPONSE_H
