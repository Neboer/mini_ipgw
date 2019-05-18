//aimed at use libcurl to make request to gateway.

#ifndef IPGW_MAKEREQUEST_H
#define IPGW_MAKEREQUEST_H
#include "getinmemory.h"

#define IPGW_REQUEST_LOGIN 0
#define IPGW_REQUEST_LOGOUT 1



requests ipgw_action(int action, char *username, char *password);


#endif //IPGW_MAKEREQUEST_H
