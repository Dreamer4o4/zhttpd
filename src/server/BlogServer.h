#ifndef _BLOGSERVER_
#define _BLOGSERVER_

#include "HttpServer.h"

class BlogServer : public base::HttpServer{
public:
    BlogServer(std::string port, int pool_size);
private:
    struct user_info{
        std::string username;
        std::string password;
    };

    void fun(base::Request &req, base::Response &res);
    void method_get(base::Request &req, base::Response &res);
    void method_post(base::Request &req, base::Response &res);
    void method_others(base::Request &req, base::Response &res);

    user_info get_user_info(std::string &body);
};

#endif