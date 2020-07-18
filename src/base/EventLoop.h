#ifndef _EVENTLOOP_
#define _EVENTLOOP_

#include <boost/noncopyable.hpp>
#include <functional>
#include <vector>
#include <memory>
#include <mutex>

#include "Epoll.h"
#include "Channel.h"

namespace base{

class EventLoop : boost::noncopyable{
    public:
        typedef std::function<void()> Functor;

        EventLoop();
        ~EventLoop(); 

        void loop();
        void quit();

        void run_in_loop(Functor cb);

        void add_channel(std::shared_ptr<Channel> &channel);
        void remove_channel(std::shared_ptr<Channel> &channel);

    private:
        void do_pending_functors();

        typedef std::vector<std::shared_ptr<Channel>> ChannelList;
        const int overtime = 1000;

        bool looping_;
        bool quit_;
        Epoll poller_;
        ChannelList active_channels_;
        std::mutex mutex_;
        std::vector<Functor> pending_functors_;
};


}

#endif