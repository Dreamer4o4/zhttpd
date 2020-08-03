#ifndef _THREADPOOL_
#define _THREADPOOL_

#include <boost/noncopyable.hpp>
#include <vector>
#include <memory>
#include <thread>

#include "TaskThread.h"
#include "Data.h"

namespace base{

class ThreadPool : boost::noncopyable{
    public:
        ThreadPool(int size) : thread_num_(size),
                                started_(false),
                                next_(0){
            for(int i=0; i<thread_num_; i++){
                threads_.push_back( std::make_unique<TaskThread>() );
            }
        }

        void start(){
            for(int i=0; i<thread_num_; i++){
                threads_[i]->start();
            }
            LOG_INFO("%d threads start", thread_num_);
        }

        EventLoop *get_next_loop(){
            EventLoop *next_loop = threads_[next_]->get_thread_loop();
            next_ = (next_ + 1) % thread_num_;
            return next_loop;
        }

    private:
        int thread_num_;
        std::vector<std::unique_ptr<TaskThread>> threads_;
        bool started_;
        int next_;
};

}

#endif