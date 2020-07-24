#include <cstring>

#include "Channel.h"
#include "EventLoop.h"
#include "Log.h"

using namespace base;

Channel::Channel(std::weak_ptr<EventLoop> loop, std::unique_ptr<Socket> &&fd)
  : loop_(loop),
    sock_(std::move(fd)),
    revents_(0),
    event_(0),
    name_("unknow"){
        ;
}

Channel::~Channel(){
    ;
}

std::unique_ptr<Socket> &Channel::sock(){
    return sock_;
}

void Channel::set_read_callback(Functor &&cb){ 
    read_callback = std::move(cb); 
}

void Channel::set_write_callback(Functor &&cb){ 
    write_callback = std::move(cb); 
}

void Channel::set_close_callback(Functor &&cb){ 
    close_callback = std::move(cb); 
}

void Channel::handle_event()
{
    std::shared_ptr<Channel> cur = shared_from_this();

    if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN))
    {
        if (close_callback) close_callback(cur);
    }
    if (revents_ & (EPOLLIN | EPOLLPRI | EPOLLRDHUP))
    {
        if (read_callback) read_callback(cur);
    }
    if (revents_ & EPOLLOUT)
    {
        if (write_callback) write_callback(cur);
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

void Channel::set_name(std::string &name){
    name_ = std::move(name);
}

std::string &Channel::name(){
    return name_;
}

void Channel::set_non_block(){
    event_ |= EPOLLET;
    sock_->set_non_block();
}


std::weak_ptr<EventLoop> Channel::get_loop(){
    return loop_;
}
