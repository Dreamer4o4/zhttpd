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

        do_pending_functors();
    }

    looping_ = false;
}

void EventLoop::run_in_loop(Functor cb){
    std::lock_guard<std::mutex> guard(mutex_);
    pending_functors_.push_back(std::move(cb));
}

void EventLoop::do_pending_functors(){
    std::vector<Functor> functors_;

    {
        std::lock_guard<std::mutex> guard(mutex_);
        functors_.swap(pending_functors_);
    }

    for(auto functor : functors_){
        functor();
    }
    functors_.clear();
}

void EventLoop::quit(){
    quit_ = true;
}

void EventLoop::add_channel(std::shared_ptr<Channel> &channel){
    poller_.add_event(channel);
}

void EventLoop::remove_channel(std::shared_ptr<Channel> &channel){
    poller_.rm_event(channel);
}
