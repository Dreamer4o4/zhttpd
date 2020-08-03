#include <cstdio>
#include <memory>

#include "EventLoop.h"
#include "Log.h"

using namespace base;

EventLoop::EventLoop()  :   looping_(false),
                            quit_(false),
                            poller_(){
    ;
}

EventLoop::~EventLoop(){
    ;
}

void EventLoop::loop(){
    if(looping_){
        LOG_ERROR("eventloop already started");
        return;
    }

    looping_ = true;
    quit_ = false;

    while(!quit_){
        poller_.wait(overtime, active_channels_);

        for(auto channel : active_channels_){
            channel->handle_event();
        }

        active_channels_.clear();

    }

    looping_ = false;
}

void EventLoop::quit(){
    quit_ = true;
}

void EventLoop::add_channel(Channel *channel){
    poller_.add_event(channel);
}

void EventLoop::remove_channel(Channel *channel){
    poller_.rm_event(channel);
}
