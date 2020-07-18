#ifndef _ACCEPTOR_
#define _ACCEPTOR_

#include <unistd.h>
#include <boost/noncopyable.hpp>
#include <thread>
#include <queue>
#include <string>
#include <functional>

#include "Data.h"
#include "Epoll.h"
#include "EventLoop.h"
#include "Channel.h"

namespace base{

// class Acceptor : boost::noncopyable{
class Acceptor{
    public:
        typedef std::function<void (int , struct data &)> Functor;

        Acceptor(std::weak_ptr<EventLoop> loop, Functor func, const std::string &port) : loop_(loop),
                                                                accept_fd_(get_resuse_sock(port.c_str())),
                                                                callback_(func),
                                                                accept_channel_(new Channel(loop_, accept_fd_)){
            
            data local("localhost", port.c_str());
            std::string name("Acceptor");
            accept_channel_->set_addr(local);
            accept_channel_->set_event(Channel::read_event);
            accept_channel_->set_read_callback(std::bind(&Acceptor::handle_read, this, std::placeholders::_1));
            accept_channel_->set_name(name);
        }

        ~Acceptor(){
            auto loop = loop_.lock();
            loop->remove_channel(accept_channel_);
            close(accept_fd_);
        }

        void start(){
            listen();
            auto loop = loop_.lock();
            loop->add_channel(accept_channel_);
        }
        
    private:
        void listen();
        int get_resuse_sock(const char *port);
        void handle_read(std::shared_ptr<Channel> &channel);

        static const int overtime = 10000;

        std::weak_ptr<EventLoop> loop_;
        int accept_fd_;
        Functor callback_;
        std::shared_ptr<Channel> accept_channel_;
};

}


#endif