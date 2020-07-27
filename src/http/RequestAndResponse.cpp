#include <cstdio>
#include <iostream>
#include <sys/stat.h>

#include "RequestAndResponse.h"
#include "Log.h"

using namespace base;

const std::map<int , std::string> Response::http_status_{
                                        {100, "Continue"},
                                        {200, "OK"},
                                        {301, "Moved Permanently"},
                                        {302, "Found"},
                                        {400, "Bad Request"},
                                        {404, "Not Found"},
                                        {500, "Internal Server Error"},
                                        {501, "Not Implemented"}
                                        };

Request::Request(std::string &req){
    parse(req);
}

int Request::equal(std::string &&key, std::string &&val){
    if(headers_.count(key)){
        if(headers_[key] == val){
            return EQUAL;
        }
        if(headers_[key].find(val) != std::string::npos){
            return ALMOST;
        }
    }
    return FALSE;
}

int Request::method_equal(std::string &&val){
    return equal("Method", std::move(val));
}

int Request::url_equal(std::string &&val){
    return equal("URL", std::move(val));
}

int Request::version_equal(std::string &&val){
    return equal("Version", std::move(val));
}

int Request::connection_equal(std::string &&val){
    return equal("Connection", std::move(val));
}

std::string Request::get_body(){
    return headers_["Body"];
}

std::string Request::get_cookie(){
    std::string res;
    if(cookies_.count("password") && cookies_.count("username")){
        res = "username=" + cookies_["username"] + "&password=" + cookies_["password"];
    }
    return res;
}

void Request::parse(std::string &msg){
    std::string request_line = get_line(msg);
    parse_line(request_line);

    std::string request_header;
    do{
        request_header = get_line(msg);
        parse_header(request_header);
    }while(!request_header.empty());

    parse_cookie();

    parse_body(msg);

    // {                                                   //测试，查看解析报文
    //     for(auto i : headers_){                                          
    //         std::cout<<i.first<<"|"<<i.second<<std::endl;
    //     }
    //     for(auto i : cookies_){
    //         std::cout<<i.first<<"|"<<i.second<<std::endl;
    //     }
    // }
}

void Request::parse_line(std::string &msg){
    size_t blank1 = msg.find_first_of(" ");
    size_t blank2 = msg.find_last_of(" ");
    headers_["Method"] = msg.substr(0, blank1);
    headers_["URL"] = msg.substr(blank1+1, blank2-blank1-1);
    headers_["Version"] = msg.substr(blank2+1);
}

void Request::parse_header(std::string &msg){
    size_t index = msg.find_first_of(":");
    if(index != std::string::npos){
        headers_[msg.substr(0, index)] = msg.substr(index+2);
    }
}

void Request::parse_cookie(){
    if(!headers_.count("Cookie")){
        return;
    }
    std::string cookie = headers_["Cookie"];
    size_t index = 0;
    while((index = cookie.find_first_of(";")) != std::string::npos){
        size_t left = cookie.find_first_not_of(" ");
        size_t mid = cookie.find_first_of("=");
        cookies_[cookie.substr(left, mid-left)] = cookie.substr(mid+1, index - mid - 1);
        cookie = cookie.substr(index + 1);
    }
    size_t left = cookie.find_first_not_of(" ");
    size_t mid = cookie.find_first_of("=");
    cookies_[cookie.substr(left, mid-left)] = cookie.substr(mid+1, index - mid - 1);
}

void Request::parse_body(std::string &msg){
    headers_["Body"] = msg;
}

std::string Request::get_line(std::string &msg){
    size_t index = msg.find_first_of("\r\n");
    std::string res = msg.substr(0, index);
    msg = msg.substr(index+2);
    return res;
}


Response::Response() : status_code_(404),
                        file_info_(),
                        send_flag_(NONE){
    set_header("Server", "zhttp");
    set_header("Connection", "Close");
    set_header("Content-Type", "text/html");
}

void Response::set_keep_alive(){
    set_header("Connection", "Keep-Alive");
}

void Response::set_status_code(int code){
    if(http_status_.count(status_code_)){
        status_code_ = code;
    }else{
        status_code_ = 501;
    }
}

void Response::set_content_type(std::string &&type){
    set_header("Content-Type", std::move(type));
}

void Response::set_body(std::string &body){
    if(send_flag_ != 0){
        LOG_WARN("has set body or file");
    }
    send_flag_ = BODY;

    body_ = std::move(body);
    set_header("Content-Length", std::to_string(body_.size()));
}

void Response::set_file(std::string &&file_name){
    if(send_flag_ != 0){
        LOG_WARN("has set body or file");
    }
    send_flag_ = FILE;

    file_info_.file_name += file_name;
    struct stat statbuf;
    if(stat(file_info_.file_name.c_str(), &statbuf)==0){
        set_header("Content-Length", std::to_string(statbuf.st_size));
    }else{
        set_status_code(404);
        file_info_.file_name = "./src/html/test.html";
        stat(file_info_.file_name.c_str(), &statbuf);
        set_header("Content-Length", std::to_string(statbuf.st_size));
    }
    file_info_.file_size = statbuf.st_size;
}

void Response::set_cookie_username(std::string &val){
    set_cookie("username", std::move(val));
}
void Response::set_cookie_password(std::string &val){
    set_cookie("password", std::move(val));
}

void Response::set_header(std::string &&key, std::string &&val){
    headers_[key] = val;
}

void Response::set_cookie(std::string &&key, std::string &&val){
    cookies_[key] = val;
}



bool Response::is_send_file(){
    return (send_flag_ == FILE);
}

Response::file_info Response::file(){
    return file_info_;
}

std::string Response::message(){
    std::string msg;
    char buf[128];

    snprintf(buf, sizeof(buf), "HTTP/1.1 %d %s\r\n", status_code_, http_status_.find(status_code_)->second.c_str());
    msg = std::string(buf);

    for (const auto& header : headers_){
        snprintf(buf, sizeof(buf), "%s: %s\r\n", header.first.c_str(), header.second.c_str());
        msg += std::string(buf);
    }

    for(const auto& cookie : cookies_){
        snprintf(buf, sizeof(buf), "Set-Cookie: %s=%s; path=/\r\n", cookie.first.c_str(), cookie.second.c_str());
        msg += std::string(buf);
    }

    msg += "\r\n";

    if(!is_send_file()){
        msg += body_;
    }

    return msg;
}