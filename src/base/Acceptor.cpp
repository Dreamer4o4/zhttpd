#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>
#include <cstdio>


#include "Acceptor.h"
#include "Log.h"

using namespace base;


Acceptor::Acceptor(std::weak_ptr<EventLoop> loop, Functor &&func, const std::string &port) : loop_(loop),
                                                                callback_(std::move(func)),
                                                                accept_channel_(std::make_shared<Channel>(loop_, std::make_unique<Socket>(data("localhost", port.c_str())) )){
            
    std::string name("Acceptor");
    accept_channel_->set_event(Channel::read_event);
    accept_channel_->set_read_callback(std::bind(&Acceptor::handle_read, this, std::placeholders::_1));
    accept_channel_->set_name(name);
}

Acceptor::~Acceptor(){
    auto loop = loop_.lock();
    loop->remove_channel(accept_channel_);
}

int Acceptor::start(){
    if(listen() != 0){
        return -1;
    }
    auto loop = loop_.lock();
    loop->add_channel(accept_channel_);
    return 0;
}

int Acceptor::listen(){
    if(accept_channel_->sock()->listen() != 0){
        return -1;
    }
    return 0;
}


void Acceptor::handle_read(std::shared_ptr<Channel> &channel){
    std::unique_ptr<Socket> client_sock = std::move(accept_channel_->sock()->accept());
    if(client_sock == nullptr){
        return ;
    }

    callback_(std::move(client_sock));

}


