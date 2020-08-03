#include <functional>
#include <vector>
#include <algorithm>
#include <string>

#include "RedisPool.h"
#include "Time.h"
#include "BlogServer.h"

/*
**  测试服务器性能
*/
// #define TEST


BlogServer::BlogServer(std::string port, int pool_size) : HttpServer(port, pool_size, std::bind(&BlogServer::fun, this, std::placeholders::_1, std::placeholders::_2)){
    ;
}

/*
**  从请求报文body里解析出用户信息
*/
BlogServer::user_info BlogServer::get_user_info(std::string &body){
    BlogServer::user_info info;
    info.username = body.substr(body.find_first_of("=") + 1, body.find_first_of("&") - body.find_first_of("=") - 1);
    info.password = body.substr(body.find_last_of("=") + 1);
    return info;
}

void BlogServer::method_get(base::Request &req, base::Response &res){
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
}

void BlogServer::method_post(base::Request &req, base::Response &res){
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
}

void BlogServer::method_others(base::Request &req, base::Response &res){
    res.set_status_code(501);
    res.set_file("test.html");
}

#ifndef TEST  
void BlogServer::fun(base::Request &req, base::Response &res){
    res.set_status_code(200);
    if(req.method_equal("GET")){
        method_get(req, res);
    }else if(req.method_equal("POST")){
        method_post(req, res);
    }else{
        method_others(req, res);
    }

    if(req.connection_equal("Keep-Alive") || 
        (req.version_equal("1.1") && !req.connection_equal("Close"))){
        res.set_keep_alive();
    }

}
#else
void BlogServer::fun(base::Request &req, base::Response &res){
    std::string usr("zh"), val("123123");
    database::redis_compare_string(usr, val);
    res.set_status_code(200);
    res.set_file("test.html");
    // std::string body("<HTML><HEAD><TITLE>zhttpd</TITLE></HEAD><BODY><h1>HELLO</h1><BODY><HTML>");
    // res.set_body(body);
    res.set_keep_alive();
}
#endif
