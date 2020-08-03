#ifndef _TASKTHREAD_
#define _TASKTHREAD_

#include <boost/noncopyable.hpp>
#include <thread>
#include <mutex>
#include <map>
#include <queue>
#include <string>
#include <sstream>

#include "EventLoop.h"
#include "Data.h"
#include "Log.h"

namespace base{

class TaskThread : boost::noncopyable{
    public:
        TaskThread();

        void start();

        EventLoop *get_thread_loop();

        static pid_t get_tid();

    private:
        void run();

        static const int overtime = 10000;

        std::unique_ptr<std::thread> thread_;
        std::queue<int> que_;
        EventLoop *loop_;
        bool started_;
        static volatile thread_local pid_t tid_;
};

}

#endif