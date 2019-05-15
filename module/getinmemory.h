// work with it.
#ifndef IPGW_GETINMENORY_H
#define IPGW_GETINMENORY_H

typedef struct {
    int code;
    char* content;
} requests;

requests Post(const char *url,const char* PostData, const char *useragent);

#endif //IPGW_GETINMENORY_H
