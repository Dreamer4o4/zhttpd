#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <cstdio>
#include <iostream>


#include "TcpServer.h"

using namespace base;

TcpServer::TcpServer(std::weak_ptr<EventLoop> loop, std::string port, int pool_size, Functor func) : loop_(loop),
                                                            acceptor_(new Acceptor(loop_, std::bind(&TcpServer::accept_func, this, std::placeholders::_1, std::placeholders::_2), port)),
                                                            request_callback_(func),
                                                            channel_id(1){
    thread_pool_ = std::make_shared<ThreadPool> (pool_size);
}

TcpServer::~TcpServer(){
    ;
}

void TcpServer::start(){
    thread_pool_->start();
    acceptor_->start();
}

void TcpServer::channel_read(std::shared_ptr<Channel> &channel){
    char buff[rec_buff_len];
    ssize_t len = 0;
    ssize_t rev_len = 0;
    memset(buff, 0, rec_buff_len);

    char response[200];
    memset(response, 0, 200);

    while((rev_len = recv(channel->fd(), &buff[len], rec_buff_len-len, 0)) > 0){
        len += rev_len;
    }
    // fprintf(stderr, "rec:%s\r\n", buff);

    request_callback_(buff, response);

    send(channel->fd(), response, sizeof(response), 0);
    // fprintf(stderr, "resp:%s\r\n\r\n\r\n",response);

    channel_close(channel);
}

void TcpServer::channel_close(std::shared_ptr<Channel> &channel){
    auto loop = channel->get_loop().lock();
    loop->remove_channel(channel);

    shutdown(channel->fd(), SHUT_WR);
    // close(channel->fd());

    auto server_loop = loop_.lock();
    server_loop->run_in_loop(std::bind(&TcpServer::delete_channel_in_map, this, channel.get()));

    channel.reset();
}

void TcpServer::delete_channel_in_map(Channel *channel){
    channel_map.erase(channel->name());
}

void TcpServer::set_no_block(int sock){
    int flags;
    
    flags = fcntl(sock, F_GETFL, NULL);

    flags |= O_NONBLOCK;

    fcntl(sock, F_SETFL, flags);

}


void TcpServer::accept_func(int fd, struct data &info){
    std::weak_ptr<EventLoop> next_loop;
    while(next_loop.expired()){
        next_loop = thread_pool_->get_next_loop();
    }

    set_no_block(fd);

    std::shared_ptr<base::Channel> channel_ptr = std::make_shared<base::Channel>(next_loop, fd);
    channel_ptr->set_addr(info);
    channel_ptr->set_event(Channel::read_event_ET);
    channel_ptr->set_read_callback(std::bind(&TcpServer::channel_read, this, std::placeholders::_1));
    channel_ptr->set_close_callback(std::bind(&TcpServer::channel_close, this, std::placeholders::_1));
    std::string name = std::string(info.client_host) + "-" +std::string(info.client_port) + "-" + std::to_string(channel_id);
    channel_map[name] = channel_ptr;
    channel_ptr->set_name(name);
    auto loop = next_loop.lock();
    loop->add_channel(channel_ptr);
    channel_id++;

    // loop->remove_channel(channel_ptr);
    // close(channel_ptr->fd());
    // channel_map.erase(channel_ptr->name());
    // channel_ptr.reset();
}