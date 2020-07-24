#include "Log.h"
#include "ThreadPool.h"
#include "TaskThread.h"
#include "Data.h"
#include "TcpServer.h"
#include "RequestAndResponse.h"
#include "HttpServer.h"

#include <string>
#include <functional>

void fun(base::Request &req, base::Response &res){
    std::string body = "<HTML>\r\n";
    body += "<HEAD><TITLE>zh</TITLE></HEAD>\r\n";
    body += "<BODY>\r\n";
    body += "<h1>HELLO</h1>\r\n";
    body += "<BODY>\r\n";
    body += "<HTML>\r\n\r\n";

    res.set_keep_alive();
    res.set_body(body);
}


int main(int argc, char *argv[]){
    std::string port("4000");

    int th_num = 8;
    if(argc > 1){
        th_num = atoi(argv[1]);
    }

    base::HttpServer hello(port, th_num, std::bind(&fun, std::placeholders::_1, std::placeholders::_2));
    hello.start();

    return 0;
}