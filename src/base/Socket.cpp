#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/sendfile.h>

#include "Socket.h"
#include "Log.h"

using namespace base;

/*
**  option for get peer address which reduced performance
*/
// #define GET_PEER_ADDR



Socket::Socket(int fd) : info_(),
                        fd_(fd),
                        listening(false),
                        block(true){
    ;
}

Socket::Socket(data &info) : info_(info),
                                fd_(get_resuse_sock(info_.client_port)),
                                listening(false),
                                block(true){
    ;
}

Socket::Socket(data &&info) : info_(info),
                                fd_(get_resuse_sock(info_.client_port)),
                                listening(false),
                                block(true){
    ;
}

int Socket::get_resuse_sock(const char *port){
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
            ::close(sock);
            continue;
        }

        if(bind(sock, tmp->ai_addr, tmp->ai_addrlen) != 0){
            ::close(sock);
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

Socket::~Socket(){
    ::close(fd_);
}

void Socket::set_non_block(){
    int flags;
    
    flags = fcntl(fd_, F_GETFL, NULL);

    flags |= O_NONBLOCK;

    fcntl(fd_, F_SETFL, flags);

    block = false;
}

void Socket::set_sock_info(data &info){
    info_ = info;
}

data &Socket::get_sock_info(){
    return info_;
}

int Socket::fd(){
    return fd_;
}

int Socket::listen(){
    if(listening){
        LOG_WARN("already listening now");
        return -1;
    }

    listening = true;
    if(::listen(fd_, 128) != 0){
        close();
        LOG_ERROR("listen failed");
        return -2;
    }

    return 0;
}

std::unique_ptr<Socket> Socket::accept(){
    if(!listening){
        LOG_WARN("not listening now");
        return std::unique_ptr<Socket>(nullptr);
    }

    struct sockaddr_storage client_addr;
    socklen_t client_addr_len = sizeof(struct sockaddr_storage);

    int client_fd = ::accept(fd_, reinterpret_cast<struct sockaddr*>(&client_addr), &client_addr_len);
    if(client_fd <= 0){
        LOG_ERROR("accept error");
        return std::unique_ptr<Socket>(nullptr);
    }

    std::unique_ptr<Socket> client_sock = std::make_unique<Socket> (client_fd);
#ifdef  GET_PEER_ADDR
    struct data client_info;
    getnameinfo(reinterpret_cast<struct sockaddr*>(&client_addr), client_addr_len, client_info.client_host, NI_MAXHOST, client_info.client_port, NI_MAXSERV, 0);
    client_sock->set_sock_info(client_info);
#endif

    return client_sock;
}

void Socket::close(){
    ::close(fd_);
}

void Socket::shutdown(int type){
    ::shutdown(fd_, type);
}

std::string Socket::read(){
    if(listening){
        LOG_WARN("listening channel can`t read");
        return std::string("");
    }

    int rec_buff_len = 1024;
    char buff[rec_buff_len];
    ssize_t len = 0;
    memset(buff, 0, rec_buff_len);

    if(block){
        len = recv(fd_, &buff[len], rec_buff_len-len, 0);
    }else{
        ssize_t rev_len = 0;
        while((rev_len = recv(fd_, &buff[len], rec_buff_len-len, 0)) > 0){
            len += rev_len;
        }
    }

    // fprintf(stderr, "req:%s\r\n\r\n\r\n",buff);          //测试，查看接收到的数据
    return std::string(buff);
}

void Socket::write(std::string &msg){
    send(fd_, msg.c_str(), msg.size(), 0);
    // fprintf(stderr, "res:%s\r\n\r\n\r\n",msg.c_str());       //测试，查看发送的数据
}

void Socket::write(std::string &&msg){
    send(fd_, msg.c_str(), msg.size(), 0);
    // fprintf(stderr, "res:%s\r\n\r\n\r\n",msg.c_str());       //测试，查看发送的数据
}

void Socket::send_file(Response::file_info info){
    int file_fd = open(info.file_name.c_str(), O_RDONLY);
    sendfile(fd_, file_fd, NULL, static_cast<size_t>(info.file_size));
    ::close(file_fd);
}