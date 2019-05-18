// work with it.
#ifndef IPGW_GETINMENORY_H
#define IPGW_GETINMENORY_H

#include <stddef.h>

typedef struct {
    int code;
    int type;
    size_t size;
    char* content;
} requests;

requests Post(const char *url,const char* PostData, const char *useragent);

#endif //IPGW_GETINMENORY_H
