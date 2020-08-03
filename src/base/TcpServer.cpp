#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <cstdio>
#include <mutex>


#include "TcpServer.h"

using namespace base;

TcpServer::TcpServer(std::string port, int pool_size, Functor &&func) : loop_(new EventLoop()),
                                                            acceptor_(std::make_unique<Acceptor>(loop_, std::bind(&TcpServer::accept_func, this, std::placeholders::_1), port)),
                                                            request_callback_(std::move(func)),
                                                            thread_pool_(std::make_unique<ThreadPool> (pool_size)){
    ;
}

TcpServer::~TcpServer(){
    ;
}

void TcpServer::start(){
    thread_pool_->start();
    
    if(acceptor_->start() != 0){
        return ;
    }

    LOG_INFO("server start");

    loop_->loop();
}

void TcpServer::channel_read(Channel *channel){
    std::string msg = std::move(channel->sock()->read());

    if(msg.size() > 0){
        request_callback_(msg, channel);
    }else{
        channel_close(channel);
    }
}

void TcpServer::channel_close(Channel *channel){
    channel->rm_from_loop();

    delete channel;
}

void TcpServer::accept_func(Socket *client_sock){
    EventLoop *next_loop = nullptr;
    while(!next_loop){
        next_loop = thread_pool_->get_next_loop();
    }

    Channel *channel_ptr = new Channel(next_loop, client_sock);
    channel_ptr->set_event(Channel::read_event | Channel::ET);
    channel_ptr->set_read_callback(std::bind(&TcpServer::channel_read, this, std::placeholders::_1));
    channel_ptr->set_close_callback(std::bind(&TcpServer::channel_close, this, std::placeholders::_1));
    channel_ptr->add_into_loop();

}