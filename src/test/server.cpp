#include <string>
#include <functional>
#include <iostream>
#include <vector>
#include <algorithm>

#include "RequestAndResponse.h"
#include "HttpServer.h"
#include "RedisTool.h"
#include "Time.h"

/*
**  测试服务器性能
*/
// #define TEST

struct user_info{
    std::string username;
    std::string password;
};

/*
**  从请求报文body里解析出用户信息
*/
user_info get_user_info(std::string &body){
    user_info info;
    info.username = body.substr(body.find_first_of("=") + 1, body.find_first_of("&") - body.find_first_of("=") - 1);
    info.password = body.substr(body.find_last_of("=") + 1);
    return info;
}

#ifndef TEST  
void fun(base::Request &req, base::Response &res){
    res.set_status_code(200);
    if(req.method_equal("GET")){
        if(req.url_equal("register.html")){
            res.set_file("register.html");
        }else if(req.url_equal("login.html")){
            res.set_file("login.html");
        }else if(req.url_equal("blog.html")){
            res.set_content_type("text/plain");
            std::string cookie = req.get_cookie();
            std::vector<std::string> blogs = database::redis_get_set(cookie);
            std::string body;
            for(auto i : blogs){
                body += (i + "\r\n\r\n");
            }
            res.set_body(body);         
        }else{
            res.set_file("judge.html");
        }
    }else if(req.method_equal("POST")){
        std::string body = req.get_body();
        if(req.url_equal("register.html")){
            user_info info = get_user_info(body);
            if(!database::redis_exists_string(info.username) && database::redis_update_string(info.username, info.password)){    //检测用户名是否已经存在
                res.set_file("success.html");
            }else{
                res.set_file("registerError.html");
            }
        }else if(req.url_equal("login.html")){
            user_info info = get_user_info(body);
            if(database::redis_compare_string(info.username, info.password)){
                res.set_file("blog.html");
                res.set_cookie_username(info.username);
                res.set_cookie_password(info.password);
            }else{
                res.set_file("loginError.html");
            }
        }else if(req.url_equal("blog.html")){
            std::string blog = base::Time::get_now_time();
            std::replace(blog.begin(), blog.end(), ' ', '-');
            blog = "time=" + blog;
            blog += body;                                     
            std::string cookie = req.get_cookie();
            database::redis_update_set(cookie, blog);
            res.set_file("blog.html");
        }
    }else{
        res.set_status_code(501);
        res.set_file("test.html");
    }

    if(req.connection_equal("Keep-Alive") || 
        (req.version_equal("1.1") && !req.connection_equal("Close"))){
        res.set_keep_alive();
    }

}
#else
void fun(base::Request &req, base::Response &res){
    res.set_status_code(200);
    res.set_file("test.html");
    // std::string body("<HTML><HEAD><TITLE>zhttpd</TITLE></HEAD><BODY><h1>HELLO</h1><BODY><HTML>");
    // res.set_body(body);
    res.set_keep_alive();
}
#endif

void test(){            //测试用例
    LOG_INFO("testing");

    std::string key("asdasd"), val1("asdasd"), val2("1231231");
    database::RedisTool::get_instance().update_set(key, val1);
    database::RedisTool::get_instance().update_set(key, val2);
    std::vector<std::string> res = database::RedisTool::get_instance().get_set(key);
    for(auto i : res){
        std::cout<<i<<std::endl;
    }

    while(1);
}

int main(int argc, char *argv[]){

    // test();

    std::string port("4000");

    int th_num = 8;
    if(argc > 1){
        th_num = atoi(argv[1]);
    }

    base::HttpServer hello(port, th_num, std::bind(&fun, std::placeholders::_1, std::placeholders::_2));
    hello.start();

    return 0;
}