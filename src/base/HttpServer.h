#ifndef _HTTPSERVER_
#define _HTTPSERVER_

#include "TcpServer.h"
#include "RequestAndResponse.h"


namespace base{

class HttpServer{
public:
    typedef std::function<void (Request &, Response &)> Functor;

    HttpServer(std::string port, int pool_size, Functor &&func) : http_callback_(std::move(func)),
                                                                server_(port, pool_size, std::bind(&HttpServer::http_read, this, std::placeholders::_1, std::placeholders::_2)){
        ;
    }

    void start(){
        server_.start();
    }
private:
    void http_read(std::string &msg, std::shared_ptr<Channel> &channel){
        Request req(msg);
        Response res;
        http_callback_(req, res);

        channel->sock()->write(res.message());
    }

    Functor http_callback_;
    TcpServer server_;
};

}

#endif