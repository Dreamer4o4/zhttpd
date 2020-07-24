#ifndef _SOCKET_
#define _SOCKET_

#include <boost/noncopyable.hpp>
#include <string>
#include <memory>

#include "Data.h"

namespace base{

class Socket : boost::noncopyable{
public:
    Socket(int fd);
    Socket(data &info);
    Socket(data &&info);

    ~Socket();

    void set_non_block();

    void set_sock_info(data &info);
    data &get_sock_info();

    int fd();

    int listen();
    std::unique_ptr<Socket> accept();
    void close();
    void shutdown(int type);

    std::string read();
    void write(std::string &msg);
    void write(std::string &&msg);

    static const int RD = SHUT_RD;
    static const int WR = SHUT_WR;
    static const int RW = SHUT_WR;

private:
    int get_resuse_sock(const char *port);

    data info_;
    int fd_;
    bool listening;
    bool block;
};

}


#endif