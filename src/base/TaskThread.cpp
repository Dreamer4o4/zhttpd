#include "TaskThread.h"
#include "Log.h"

using namespace base;

volatile thread_local pid_t TaskThread::tid_ = 0;

TaskThread::TaskThread() : que_(),
            started_(false){
    ;
}

void TaskThread::start(){
    if(started_){
        LOG_ERROR("thread has been started");
        return ;
    }

    thread_ = std::make_unique<std::thread>(std::bind(&TaskThread::run, this));
    thread_->detach();
    
    started_ = true;
}

EventLoop *TaskThread::get_thread_loop(){
    return loop_;
}

pid_t TaskThread::get_tid(){
    return TaskThread::tid_;
}

void TaskThread::run(){
    // LOG_INFO("tid_: %d start", gettid());
    tid_ = gettid();
    
    EventLoop loop;
    loop_ = &loop;
    loop.loop();
    loop_ = NULL;
}