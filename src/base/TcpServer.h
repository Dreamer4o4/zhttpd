#ifndef _TCPSERVER_
#define _TCPSERVER_

#include <boost/noncopyable.hpp>
#include <memory>
#include <string>
#include <cstdio>

#include "Acceptor.h"
#include "ThreadPool.h"

namespace base{

class TcpServer : boost::noncopyable{
    public:
        typedef std::function<void (char *, char *)> Functor;
        
        TcpServer(std::string port, int pool_size, Functor func) : acceptor_(new Acceptor(std::bind(&TcpServer::accept_func, this, std::placeholders::_1), port)),
                                                            request_callback_(func){
            thread_pool_ = std::make_shared<ThreadPool> (pool_size, std::bind(&TcpServer::thread_func, this, std::placeholders::_1));
        }

        void start(){
            thread_pool_->start();
            acceptor_->start();
        }
    private:
        void thread_func(int arg){
            char buff[rec_buff_len];
            ssize_t len = 0;
            ssize_t rev_len = 0;
            memset(buff, 0, rec_buff_len);

            char response[200];
            memset(response, 0, 200);

            while((rev_len = recv(arg, &buff[len], rec_buff_len-len, 0)) > 0){
                len += rev_len;
            }
            // fprintf(stderr, "rec:%s\r\n", buff);

            request_callback_(buff, response);

            send(arg, response, sizeof(response), 0);
            // fprintf(stderr, "resp:%s\r\n\r\n\r\n",response);

            // shutdown(arg, SHUT_WR);
            close(arg);
        }

        void accept_func(std::shared_ptr<struct data> arg){
            thread_pool_->add_task(arg);
        }

        static const int rec_buff_len = 512;

        std::unique_ptr<Acceptor> acceptor_;
        Functor request_callback_;
        std::shared_ptr<ThreadPool> thread_pool_;
};

}


#endif