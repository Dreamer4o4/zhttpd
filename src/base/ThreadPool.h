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
        typedef std::function<void (int)> Functor;

        ThreadPool(int size, Functor func) : thread_num_(size),
                                    thread_function_(func),
                                    started_(false),
                                    next_(0){
            for(int i=0; i<thread_num_; i++){
                threads_.push_back( std::unique_ptr<TaskThread> (new TaskThread(thread_function_)) );
            }
        }

        void start(){
            for(int i=0; i<thread_num_; i++){
                threads_[i]->start();
            }
        }

        void add_task(std::shared_ptr<struct data> info){
            threads_[next_]->add_task(info, Epoll::Type::ET);
            next_++;
            if(next_ >= thread_num_){
                next_ = 0;
            }
        }

    private:
        int thread_num_;
        Functor thread_function_;
        std::vector<std::unique_ptr<TaskThread>> threads_;
        bool started_;
        int next_;
};

}

#endif