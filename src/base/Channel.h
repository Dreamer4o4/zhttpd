#ifndef _CHANNEL_
#define _CHANNEL_

#include <boost/noncopyable.hpp>
#include <functional>
#include <memory>
#include <sys/epoll.h>
#include <string>

#include "Data.h"

namespace base{

class EventLoop;

class Channel : boost::noncopyable, public std::enable_shared_from_this<Channel>{
    public:
        typedef std::function<void(std::shared_ptr<Channel> &)> Functor;

        Channel(std::weak_ptr<EventLoop> loop, int fd);
        ~Channel();

        int fd();

        void set_read_callback(Functor &&cb);
        void set_write_callback(Functor &&cb);
        void set_close_callback(Functor &&cb);

        void handle_event();
        void set_revents(int revt);

        void set_event(uint32_t event);
        uint32_t event();

        void set_addr(data &addr);
        char* addr_ip();
        char* addr_port();
        void set_name(std::string &name);
        std::string name();

        std::weak_ptr<EventLoop> get_loop();

        // void add();
        // void remove();

        static const int read_event = EPOLLIN;
        static const int read_event_ET = EPOLLIN | EPOLLET;
        static const int write_event = EPOLLOUT;

    private:
        std::weak_ptr<EventLoop> loop_;
        int fd_;
        int revents_;       //events that epoll wait return
        uint32_t event_;    // set the events that epoll listens to
        struct data addr_;
        std::string name_;

        Functor read_callback;
        Functor write_callback;
        Functor close_callback;
};

}

#endif