//All requests will be made by the file. Based on the getitinmemory.c
#include "makerequest.h"
#include "settings.h"
#include <string.h>
#include <stdlib.h>

char *str_replace(char *orig, char *rep, char *with) { // aimed at replace string in c, from stackoverflow.
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep (the string to remove)
    int len_with; // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    // sanity checks and initialization
    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
    if (!with)
        with = "";
    len_with = strlen(with);

    // count the number of replacements needed
    ins = orig;
    for (count = 0; (tmp = strstr(ins, rep)); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    // first time through the loop, all the variable are set correctly
    // from here on,
    //	tmp points to the end of the result string
    //	ins points to the next occurrence of rep in orig
    //	orig points to the remainder of orig after "end of rep"
    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}

requests ipgw_action(int action, char *username, char *password) {
    char* postdata = getPostData(action);
    requests req;
    req.code = 0, req.content = NULL;
    if(!postdata) return req;
    char* data_will_be_passed = str_replace(str_replace(postdata,"${username}",username)
            ,"${password}",password);
    char* url = getSettingsData("log_url");
    char* ua = getSettingsData("useragent");
    if(!url || !ua) return req;
    req = Post(url, data_will_be_passed, ua);
    return req;
}