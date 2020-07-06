#ifndef _TCPSERVER_
#define _TCPSERVER_

#include <boost/noncopyable.hpp>
#include <memory>
#include <string>
#include <cstdio>

#include "Acceptor.h"
#include "ThreadPool.h"
#include "Channel.h"

namespace base{

class TcpServer : boost::noncopyable{
    public:
        typedef std::function<void (char *, char *)> Functor;
        
        TcpServer(EventLoop *loop, std::string port, int pool_size, Functor func) : loop_(loop),
                                                            acceptor_(new Acceptor(loop_, std::bind(&TcpServer::accept_func, this, std::placeholders::_1, std::placeholders::_2), port)),
                                                            request_callback_(func){
            thread_pool_ = std::make_shared<ThreadPool> (pool_size);
        }

        void start(){
            thread_pool_->start();
            acceptor_->start();
        }


    private:
        void handle_read(Channel *channel){

            char buff[rec_buff_len];
            ssize_t len = 0;
            ssize_t rev_len = 0;
            memset(buff, 0, rec_buff_len);

            char response[200];
            memset(response, 0, 200);

            while((rev_len = recv(channel->fd(), &buff[len], rec_buff_len-len, 0)) > 0){
                len += rev_len;
            }
            fprintf(stderr, "rec:%s\r\n", buff);

            request_callback_(buff, response);

            send(channel->fd(), response, sizeof(response), 0);
            fprintf(stderr, "resp:%s\r\n\r\n\r\n",response);

            shutdown(channel->fd(), SHUT_WR);
            // close(channel->fd());

            // fprintf(stderr, "handle read\r\n");
            channel->remove();
        }

        void accept_func(int fd, struct data &info){
            EventLoop *next_loop = NULL;
            while(!next_loop){
                next_loop = thread_pool_->get_next_loop();
            }
            std::shared_ptr<Channel> channel_ptr = std::make_shared<Channel>(next_loop, fd);
            channel_ptr->set_addr(info);
            channel_ptr->set_event(Channel::read_event_ET);
            channel_ptr->setReadCallback(std::bind(&TcpServer::handle_read, this, std::placeholders::_1));
            channel_ptr->add();

            // ::close(channel_ptr->fd());
            // fprintf(stderr, "close fd: %d\r\n", channel_ptr->fd());
            // fprintf(stderr, "%s\r\n%s\r\n", info.client_host, info.client_port);
        }

        static const int rec_buff_len = 512;

        EventLoop *loop_;
        std::unique_ptr<Acceptor> acceptor_;
        Functor request_callback_;
        std::shared_ptr<ThreadPool> thread_pool_;
};

}


#endif