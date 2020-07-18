#include "Log.h"
#include "ThreadPool.h"
#include "TaskThread.h"
#include "Data.h"
#include "TcpServer.h"
#include "EventLoop.h"
#include "Acceptor.h"

#include <iostream>
#include <string>
#include <stdlib.h>
#include <netdb.h>
#include <functional>

void fun(char *recv, char *response){
    strcat(response,"HTTP/1.0 200 OK\r\n");
    strcat(response,"Server: zhttp\r\n");
    strcat(response,"Content-Type: text/html\r\n");
    strcat(response,"\r\n");
    strcat(response,"<HTML>\r\n");
    strcat(response,"<HEAD><TITLE>zh</TITLE></HEAD>\r\n");

    strcat(response,"<BODY>\r\n");
    strcat(response,"<h1>HELLO</h1>\r\n");
    strcat(response,"</BODY>\r\n");

    strcat(response,"</HTML>\r\n");
}

typedef std::function<void (int , struct data &)> Functor;

int main(int argc, char *argv[]){
    std::string port("4000");

    int th_num = 8;
    if(argc > 1){
        th_num = atoi(argv[1]);
    }

    std::shared_ptr<base::EventLoop> loop = std::make_shared<base::EventLoop>();
    base::TcpServer hello(loop, port, th_num, std::bind(&fun, std::placeholders::_1, std::placeholders::_2));
    hello.start();
    std::cout<<"server start"<<std::endl;
    loop->loop();

    return 0;
}