#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <cstdio>
#include <mutex>


#include "TcpServer.h"

using namespace base;


/*
**  option for non_block I/O, EPOLL_ET
*/
#define NONBLOCK

TcpServer::TcpServer(std::string port, int pool_size, Functor &&func) : loop_(std::make_shared<EventLoop>()),
                                                            acceptor_(std::make_unique<Acceptor>(loop_, std::bind(&TcpServer::accept_func, this, std::placeholders::_1), port)),
                                                            request_callback_(std::move(func)),
                                                            thread_pool_(std::make_shared<ThreadPool> (pool_size)),
                                                            channel_id(1){
    ;
}

TcpServer::~TcpServer(){
    for(auto &channel : channel_map){
        channel_close(channel.second);
    }
}

void TcpServer::start(){
    thread_pool_->start();
    
    if(acceptor_->start() != 0){
        return ;
    }

    loop_->loop();
}

void TcpServer::channel_read(std::shared_ptr<Channel> &channel){
    std::string msg = std::move(channel->sock()->read());

    if(msg.size() > 0){
        request_callback_(msg, channel);
    }else{
        channel_close(channel);
    }
}

void TcpServer::channel_close(std::shared_ptr<Channel> &channel){
    auto loop = channel->get_loop().lock();
    loop->remove_channel(channel);

    // channel->sock()->close();

    // {
    //     std::lock_guard<std::mutex> guard(mutex_);
    //     channel_map.erase(channel->name());
    // }
    loop_->run_in_loop(std::bind(&TcpServer::delete_channel_in_map, this, channel.get()));

    channel.reset();
}

void TcpServer::delete_channel_in_map(Channel *channel){
    channel_map.erase(channel->name());
}

void TcpServer::accept_func(std::unique_ptr<Socket> &&client_sock){
    std::weak_ptr<EventLoop> next_loop;
    while(next_loop.expired()){
        next_loop = thread_pool_->get_next_loop();
    }

    std::string name = std::string(client_sock->get_sock_info().client_host) + "-" +std::string(client_sock->get_sock_info().client_port) + "-" + std::to_string(channel_id);
    std::shared_ptr<base::Channel> channel_ptr = std::make_shared<base::Channel>(next_loop, std::move(client_sock));
    channel_ptr->set_event(Channel::read_event);
#ifdef NONBLOCK
    channel_ptr->set_non_block();
#endif
    channel_ptr->set_read_callback(std::bind(&TcpServer::channel_read, this, std::placeholders::_1));
    channel_ptr->set_close_callback(std::bind(&TcpServer::channel_close, this, std::placeholders::_1));
    // {
    //     std::lock_guard<std::mutex> guard(mutex_);
    //     channel_map[name] = channel_ptr;
    // }
    channel_map[name] = channel_ptr;
    channel_ptr->set_name(name);
    auto loop = next_loop.lock();
    loop->add_channel(channel_ptr);
    channel_id++;

}