#ifndef _TASKTHREAD_
#define _TASKTHREAD_

#include <boost/noncopyable.hpp>
#include <thread>
#include <mutex>
#include <functional>
#include <map>
#include <queue>
#include <string>
#include <sstream>

#include "Epoll.h"
#include "Data.h"
#include "Log.h"
#include "BlockingQueue.h"

namespace base{

class TaskThread : boost::noncopyable{
    public:
        typedef std::function<void (int)> Functor;

        TaskThread(const Functor &func) : thread_function_(func),
                                        que_(),
                                        ep_(),
                                        started_(false),
                                        tid(0){
            ;
        }

        void start(){
            if(started_){
                LOG_ERROR("thread has been started");
                return ;
            }

            thread_ = std::make_shared<std::thread>(std::bind(&TaskThread::run, this));

            std::ostringstream oss;
            oss << thread_->get_id();
            std::string stid = oss.str();
            tid = std::stoull(stid);

            std::string info = "tid:" + std::to_string(tid) + " start";
            LOG_INFO(info);

            thread_->detach();
            
            started_ = true;
        }

        bool add_task(std::shared_ptr<struct data> info, int type){
            return ep_.add_event(info->fd, type);
        }

    private:
        void run(){
            for(;;){
                if(ep_.wait(overtime, que_) > 0 || que_.size() != 0){
                    while(que_.size()){
                        int fd = que_.front();
                        que_.pop();
                        ep_.rm_event(fd);

                        thread_function_(fd);

                    }
                }else{
                    std::string info = "tid:" + std::to_string(tid) + " still alive";
                    LOG_INFO(info);
                }
            }
        }

        static const int overtime = 10000;

        Functor thread_function_;
        std::shared_ptr<std::thread> thread_;
        std::queue<int> que_;
        Epoll ep_;
        bool started_;
        std::map<int, std::shared_ptr<struct data>> map_;
        unsigned long long tid;
};

}

#endif