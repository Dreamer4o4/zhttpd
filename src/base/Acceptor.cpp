#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>


#include "Acceptor.h"
#include "Log.h"

using namespace base;

int Acceptor::get_resuse_sock(const char *port){
    int sock, optval = 1;
    struct addrinfo hint;
    struct addrinfo *res, *tmp;

    memset(&hint, 0, sizeof(struct addrinfo));
    hint.ai_flags = AI_PASSIVE | AI_NUMERICSERV;
    hint.ai_family = AF_UNSPEC;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_protocol = 0;
    hint.ai_addrlen = 0;
    hint.ai_addr = NULL;
    hint.ai_canonname = NULL;
    hint.ai_next = NULL;
    if(getaddrinfo(NULL, port, &hint, &res) != 0){
        LOG_ERROR("getaddrinfo failed");
        return -1;
    }

    for(tmp = res; tmp != NULL; res = res->ai_next, tmp = res){
        sock = socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);
        if(sock < 0){
            continue;
        }

        if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1){
            close(sock);
            continue;
        }

        if(bind(sock, tmp->ai_addr, tmp->ai_addrlen) != 0){
            close(sock);
            continue;
        }

        break;
    }
    if(tmp == NULL){
        LOG_ERROR("can not get a acceptor socket");
        return -1;
    }
    freeaddrinfo(res);

    return sock;
}

void Acceptor::listen(){
    if(accept_fd_ <= 0){
        return ;
    }

    if(::listen(accept_fd_, 10) != 0){
        close(accept_fd_);
        LOG_ERROR("listen failed");
        return ;
    }

    ep_.add_event(accept_fd_, Epoll::LT);
}

void Acceptor::start(){
    thread_ = std::make_shared<std::thread> (std::bind(&Acceptor::run, this));
}

void Acceptor::run(){

    for(;;){
        ep_.wait(overtime, listen_queue_);

        while(listen_queue_.size() != 0){
            struct sockaddr_storage client_addr;
            socklen_t client_addr_len = sizeof(struct sockaddr_storage);

            int tmp = listen_queue_.pop();

            int client_fd = accept(tmp, reinterpret_cast<struct sockaddr*>(&client_addr), &client_addr_len);
            if(client_fd <= 0){
                continue;
            }

            std::shared_ptr<struct data> client_info = std::make_shared<struct data>(client_fd);
            if(getnameinfo(reinterpret_cast<struct sockaddr*>(&client_addr), client_addr_len, client_info->client_host, NI_MAXHOST, client_info->client_server, NI_MAXSERV, 0) != 0){
                strcpy(client_info->client_host, "unkonw");
                strcpy(client_info->client_server, "unkonw");
            }

            set_no_block(client_fd);

            callback_(client_info);
        }

    }
}

void Acceptor::set_no_block(int sock){
    int flags;
	
	flags = fcntl(sock, F_GETFL, NULL);
 
	flags |= O_NONBLOCK;
 
	fcntl(sock, F_SETFL, flags);

}
