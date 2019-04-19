#include <iostream>
#include <curl/curl.h>

using namespace std;

int main(int argc, char *argv[]) {// programme entrance
    CURL *curl;             //定义CURL类型的指针
    CURLcode res;           //定义CURLcode类型的变量，保存返回状态码
    if (argc != 2) {
        printf("Usage : file <url>;\n");
        exit(1);
    }

    curl = curl_easy_init();        //初始化一个CURL类型的指针
    if (curl != nullptr) {
        //设置curl选项. 其中CURLOPT_URL是让用户指 定url. argv[1]中存放的命令行传进来的网址
        curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
        //调用curl_easy_perform 执行我们的设置.并进行相关的操作. 在这里只在屏幕上显示出来.
        res = curl_easy_perform(curl);
        //清除curl操作.
        curl_easy_cleanup(curl);
    }
    return 0;
}