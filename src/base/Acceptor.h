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

class Acceptor : boost::noncopyable{
    public:
        typedef std::function<void (std::unique_ptr<Socket> &&)> Functor;

        Acceptor(std::weak_ptr<EventLoop> loop, Functor &&func, const std::string &port);

        ~Acceptor();

        int start();
        
    private:
        int listen();

        void handle_read(std::shared_ptr<Channel> &channel);

        static const int overtime = 10000;

        std::weak_ptr<EventLoop> loop_;
        Functor callback_;
        std::shared_ptr<Channel> accept_channel_;
};

}


#endif