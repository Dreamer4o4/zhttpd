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

        Acceptor(EventLoop *loop, Functor func, const std::string &port) : loop_(loop),
                                                                accept_fd_(get_resuse_sock(port.c_str())),
                                                                callback_(func),
                                                                accept_channel_(loop_, accept_fd_){
            
            accept_channel_.set_addr(data ("localhost", port.c_str()));
            accept_channel_.set_event(Channel::read_event);
            accept_channel_.setReadCallback(std::bind(&Acceptor::handle_read, this, std::placeholders::_1));
        }

        ~Acceptor(){
            accept_channel_.remove();
            close(accept_fd_);
        }

        void start(){
            listen();
            accept_channel_.add();
        }
        
    private:
        void listen();
        int get_resuse_sock(const char *port);
        void handle_read(Channel *channel);
        void set_no_block(int sock);

        static const int overtime = 10000;

        EventLoop *loop_;
        int accept_fd_;
        Functor callback_;
        Channel accept_channel_;
};

}


#endif