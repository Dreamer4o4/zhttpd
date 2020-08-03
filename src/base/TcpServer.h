#ifndef _TCPSERVER_
#define _TCPSERVER_

#include <boost/noncopyable.hpp>
#include <memory>
#include <map>
#include <string>

#include "Acceptor.h"
#include "ThreadPool.h"
#include "Channel.h"
#include "Data.h"
#include "Socket.h"

namespace base{

class TcpServer : boost::noncopyable{
    public:
        typedef std::function<void (std::string &, Channel *)> Functor;
        
        TcpServer(std::string port, int pool_size, Functor &&func);

        ~TcpServer();

        void start();

    private:
        void channel_read(Channel *channel);
        void channel_close(Channel *channel);

        void accept_func(Socket *client_sock);

        static const int rec_buff_len = 512;

        EventLoop *loop_;
        std::unique_ptr<Acceptor> acceptor_;
        Functor request_callback_;
        std::unique_ptr<ThreadPool> thread_pool_;
};

}


#endif