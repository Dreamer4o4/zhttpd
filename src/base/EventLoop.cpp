#include <cstdio>

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
        channels_.clear();
        poller_.wait(overtime, channels_);

        for(auto channel : channels_){
            channel->handleEvent();
        }
    }

    looping_ = false;
}

void EventLoop::quit(){
    quit_ = true;
}

void EventLoop::add_channel(Channel* channel){
    poller_.add_event(channel);
}

void EventLoop::remove_channel(Channel* channel)
{
  poller_.rm_event(channel);
}
