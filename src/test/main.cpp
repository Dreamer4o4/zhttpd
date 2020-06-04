#include "Log.h"
#include "BlockingQueue.h"
#include "ThreadPool.h"
#include "TaskThread.h"
#include "Data.h"
#include "TcpServer.h"

#include <iostream>
#include <string>
#include <stdlib.h>
#include <netdb.h>


void test(std::shared_ptr<struct base::data> arg){
    std::cout<<arg->fd<<std::endl;
    std::cout<<arg->client_host<<std::endl;
    std::cout<<arg->client_server<<std::endl;
    close(arg->fd);
}

void fun(){
    static int i = 0; 
    std::cout<<"time : "<<i++<<std::endl;
}



int main(int argc, char *argv[]){
    std::string port("4000");
    int th_num = 1;

    if(argc > 1){
        th_num = atoi(argv[1]);
    }
    base::TcpServer hello(port, th_num, std::bind(&fun));
    hello.start();

    // base::Acceptor ac(std::bind(test, std::placeholders::_1), port);
    // ac.start();


    while(1);

    return 0;
}