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
        typedef std::function<void (std::string &, std::shared_ptr<Channel> &)> Functor;
        
        TcpServer(std::string port, int pool_size, Functor &&func);

        ~TcpServer();

        void start();

    private:
        void channel_read(std::shared_ptr<Channel> &channel);
        void channel_close(std::shared_ptr<Channel> &channel);

        void accept_func(std::unique_ptr<Socket> &&client_sock);

        void delete_channel_in_map(Channel *channel);

        static const int rec_buff_len = 512;

        std::shared_ptr<EventLoop> loop_;
        std::unique_ptr<Acceptor> acceptor_;
        Functor request_callback_;
        std::shared_ptr<ThreadPool> thread_pool_;
        int channel_id;
        std::map<std::string, std::shared_ptr<base::Channel>> channel_map;
        std::mutex mutex_;
};

}


#endif