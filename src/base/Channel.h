#ifndef _CHANNEL_
#define _CHANNEL_

#include <boost/noncopyable.hpp>
#include <functional>
#include <memory>
#include <sys/epoll.h>

#include "Data.h"

namespace base{

class EventLoop;

class Channel : boost::noncopyable{
    public:
        typedef std::function<void(Channel *)> Functor;

        Channel(EventLoop *loop, int fd);
        ~Channel();

        int fd();

        void setReadCallback(Functor &&cb);
        void setWriteCallback(Functor &&cb);
        void setCloseCallback(Functor &&cb);

        void handleEvent();
        void set_revents(int revt);

        void set_event(uint32_t event);
        uint32_t event();

        void set_addr(data addr);
        char* addr_ip();
        char* addr_port();

        void add();
        void remove();

        static const int read_event = EPOLLIN;
        static const int read_event_ET = EPOLLIN | EPOLLET;
        static const int write_event = EPOLLOUT;

    private:
        EventLoop *loop_;
        int fd_;
        int revents_;       //events that epoll wait return
        uint32_t event_;    // set the events that epoll listens to
        struct data addr_;

        Functor read_callback;
        Functor write_callback;
        Functor close_callback;
};

}

#endif