#include <cstring>

#include "Channel.h"
#include "EventLoop.h"
#include "Log.h"

using namespace base;

Channel::Channel(EventLoop *loop, Socket *fd)
  : loop_(loop),
    sock_(fd),
    revents_(0),
    event_(0){
        ;
}

Channel::~Channel(){
    delete sock_;
}

Socket *Channel::sock(){
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
    if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN))
    {
        if (close_callback) close_callback(this);
    }
    if (revents_ & (EPOLLIN | EPOLLPRI | EPOLLRDHUP))
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

void Channel::add_into_loop(){
    loop_->add_channel(this);
}

void Channel::rm_from_loop(){
    loop_->remove_channel(this);
}
