#ifndef _EVENTLOOP_
#define _EVENTLOOP_

#include <boost/noncopyable.hpp>
#include <functional>
#include <vector>
#include <memory>

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

        // void runInLoop(Functor cb);
        // void queueInLoop(Functor cb);

        void add_channel(Channel* channel);
        void remove_channel(Channel* channel);

    private:
        typedef std::vector<Channel*> ChannelList;
        const int overtime = 1000;

        bool looping_;
        bool quit_;
        Epoll poller_;
        ChannelList channels_;
};


}

#endif