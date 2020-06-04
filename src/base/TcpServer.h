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
        typedef std::function<void ()> Functor;
        
        TcpServer(std::string port, int pool_size, Functor func) : acceptor_(new Acceptor(std::bind(&TcpServer::accept_func, this, std::placeholders::_1), port)),
                                                            request_callback_(func){
            thread_pool_ = std::make_shared<ThreadPool> (pool_size, std::bind(&TcpServer::thread_func, this, std::placeholders::_1));
        }

        void start(){
            thread_pool_->start();
            acceptor_->start();

            fprintf(stderr, "server start\r\n");
            
            for(;;);
        }
    private:
        void thread_func(std::shared_ptr<struct data> arg){
            char buff[rec_buff_len];
            ssize_t len = 0;
            ssize_t rev_len = 0;
            memset(buff, 0, rec_buff_len);
            while((rev_len = recv(arg->fd, &buff[len], rec_buff_len-len, 0)) > 0){
                len += rev_len;
            }
            printf("rec:%s\r\n", buff);

            char response[200];
            memset(response, 0, 200);

            request_callback_();

            strcat(response,"HTTP/1.0 200 OK\r\n");
            strcat(response,"Server: zhttp\r\n");
            strcat(response,"Content-Type: text/html\r\n");
            strcat(response,"\r\n");
            strcat(response,"<HTML>\r\n");
            strcat(response,"<HEAD><TITLE>zh</TITLE></HEAD>\r\n");

            strcat(response,"<BODY>\r\n");
            strcat(response,"<h1>HELLO</h1>\r\n");
            strcat(response,"</BODY>\r\n");

            strcat(response,"</HTML>\r\n");
            send(arg->fd, response, sizeof(response), 0);
            fprintf(stderr, "resp:%s\r\n",response);

            shutdown(arg->fd, SHUT_WR);
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