#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>
#include <cstdio>


#include "Acceptor.h"
#include "Log.h"

using namespace base;


Acceptor::Acceptor(EventLoop *loop, Functor &&func, const std::string &port) : loop_(loop),
                                                                callback_(std::move(func)),
                                                                accept_channel_(std::make_shared<Channel>(loop_, new Socket(data("localhost", port.c_str()), false) )){
            
    accept_channel_->set_event(Channel::read_event);
    accept_channel_->set_read_callback(std::bind(&Acceptor::handle_read, this, std::placeholders::_1));
}

Acceptor::~Acceptor(){
    loop_->remove_channel(accept_channel_.get());
}

int Acceptor::start(){
    if(listen() != 0){
        return -1;
    }
    loop_->add_channel(accept_channel_.get());
    return 0;
}

int Acceptor::listen(){
    if(accept_channel_->sock()->listen() != 0){
        return -1;
    }
    return 0;
}

void Acceptor::handle_read(Channel *channel){
    Socket *client_sock = accept_channel_->sock()->accept();
    if(client_sock == nullptr){
        return ;
    }

    callback_(client_sock);
}


