#ifndef _SOCKET_
#define _SOCKET_

#include <boost/noncopyable.hpp>
#include <string>
#include <memory>

#include "Data.h"
#include "RequestAndResponse.h"

namespace base{

class Socket : boost::noncopyable{
public:
    Socket(int fd);
    Socket(data &info, bool nonblock);
    Socket(data &&info, bool nonblock);

    ~Socket();

    void set_sock_info(data &info);
    data &get_sock_info();

    int fd();

    int listen();
    Socket *accept();       //accept nonblock-socket
    void close();
    void shutdown(int type);

    std::string read();
    void write(std::string &msg);
    void write(std::string &&msg);
    void send_file(Response::file_info info);

    void set_non_block();

    static const int RD = SHUT_RD;
    static const int WR = SHUT_WR;
    static const int RW = SHUT_WR;
private:
    int get_sock(const char *port, bool nonblock);

    data info_;
    int fd_;
    bool listening;
    bool block;
};

}


#endif