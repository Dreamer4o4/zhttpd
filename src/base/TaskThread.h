#ifndef _TASKTHREAD_
#define _TASKTHREAD_

#include <boost/noncopyable.hpp>
#include <thread>
#include <mutex>
#include <functional>
#include <map>

#include "BlockingQueue.h"
#include "Epoll.h"
#include "Data.h"

namespace base{

class TaskThread : boost::noncopyable{
    public:
        typedef std::function<void (std::shared_ptr<struct data>)> Functor;

        TaskThread(const Functor &func) : thread_function_(func),
                                        que_(),
                                        ep_(),
                                        started_(false),
                                        map_(){
            ;
        }

        void start(){
            if(started_){
                LOG_ERROR("thread has been started");
                return ;
            }

            thread_ = std::make_shared<std::thread>(std::bind(&TaskThread::run, this));
            thread_->detach();
            
            started_ = true;
        }

        bool add_task(std::shared_ptr<struct data> info, int type){
            map_.insert(std::pair<int, std::shared_ptr<struct data>>(info->fd, info));
            return ep_.add_event(info->fd, type);
        }



    private:
        void run(){
            for(;;){
                if(ep_.wait(overtime, que_) > 0 || que_.size() != 0){
                    while(que_.size()){
                        int fd = que_.pop();
                        ep_.rm_event(fd);
                        if(map_.find(fd) == map_.end()){
                            continue;
                        }
                        thread_function_(map_[fd]);
                        map_.erase(fd);
                    }
                }
            }
        }

        static const int overtime = 10000;

        Functor thread_function_;
        std::shared_ptr<std::thread> thread_;
        BlockingQueue<int> que_;
        Epoll ep_;
        bool started_;
        std::map<int, std::shared_ptr<struct data>> map_;
};

}

#endif