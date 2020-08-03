#ifndef _CHANNEL_
#define _CHANNEL_

#include <boost/noncopyable.hpp>
#include <functional>
#include <memory>
#include <sys/epoll.h>
#include <string>

#include "Data.h"
#include "Socket.h"

namespace base{

class EventLoop;

class Channel : boost::noncopyable{
    public:
        typedef std::function<void(Channel *)> Functor;

        Channel(EventLoop *loop, Socket *fd);
        ~Channel();

        Socket *sock();

        void set_read_callback(Functor &&cb);           //set the callback function of the current Channel event
        void set_write_callback(Functor &&cb);
        void set_close_callback(Functor &&cb);

        void handle_event();                            //EventLoop call, call the callback function according to the revent
        void set_revents(int revt);                     //Epoll call, set the type of revent

        void set_event(uint32_t event);                 //set to listen the current Channel event
        uint32_t event();

        void add_into_loop();
        void rm_from_loop();

        static const int read_event = EPOLLIN;
        static const int write_event = EPOLLOUT;
        static const int ET = EPOLLET;

    private:
        EventLoop *loop_;
        Socket *sock_;
        int revents_;                                   //events that epoll wait return
        uint32_t event_;                                //set the events that epoll listens to

        Functor read_callback;
        Functor write_callback;
        Functor close_callback;
};

}

#endif