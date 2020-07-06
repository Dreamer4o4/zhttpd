#include <cstring>

#include "Channel.h"
#include "EventLoop.h"

using namespace base;

Channel::Channel(EventLoop* loop, int fd__)
  : loop_(loop),
    fd_(fd__),
    revents_(0),
    event_(0),
    addr_(){
        ;
}

Channel::~Channel(){
    ;
}

int Channel::fd(){
    return fd_;
}

void Channel::setReadCallback(Functor &&cb){ 
    read_callback = std::move(cb); 
}

void Channel::setWriteCallback(Functor &&cb){ 
    write_callback = std::move(cb); 
}

void Channel::setCloseCallback(Functor &&cb){ 
    close_callback = std::move(cb); 
}

void Channel::handleEvent()
{
    if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN))
    {
        if (close_callback) close_callback(this);
    }
    // if (revents_ & (EPOLLIN | EPOLLPRI | EPOLLRDHUP))
    if (revents_ & EPOLLIN)
    {
        if (read_callback) read_callback(this);
    }
    if (revents_ & EPOLLOUT)
    {
        if (write_callback) write_callback(this);
    }
}

void Channel::set_revents(int revt){
    revents_ = revt;
}

void Channel::set_event(uint32_t event){
    event_ = event;
}

uint32_t Channel::event(){
    return event_;
}

void Channel::set_addr(data addr){
    strcpy(addr_.client_host, addr.client_host);
    strcpy(addr_.client_port, addr.client_port);
}

char* Channel::addr_ip(){
    return addr_.client_host;
}

char* Channel::addr_port(){
    return addr_.client_port;
}

void Channel::add(){
    loop_->add_channel(this);
}

void Channel::remove(){
    loop_->remove_channel(this);
}