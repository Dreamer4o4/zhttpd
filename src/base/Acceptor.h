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
#include "BlockingQueue.h"

namespace base{

class Acceptor : boost::noncopyable{
    public:
        typedef std::function<void (std::shared_ptr<struct data>)> Functor;

        Acceptor(Functor func, const std::string &port) : callback_(func),
                                                        ep_(),
                                                        listen_queue_(){
            accept_fd_ = get_resuse_sock(port.c_str());
            listen();
        }

        ~Acceptor(){
            close(accept_fd_);
        }
        
        void start();
    private:
        void listen();
        int get_resuse_sock(const char *port);
        void run();
        void set_no_block(int sock);

        static const int overtime = 10000;

        int accept_fd_;
        Functor callback_;
        Epoll ep_;
        BlockingQueue<int> listen_queue_;
        std::shared_ptr<std::thread> thread_;
};

}


#endif