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

bool Request::equal(std::string &&key, std::string &&val){
    if(headers_.count(key) && headers_[key].find(val) != std::string::npos){
        return true;
    }
    return false;
}

void Request::parse(std::string &msg){
    std::string request_line = get_line(msg);
    parse_line(request_line);

    std::string request_header;
    do{
        request_header = get_line(msg);
        parse_header(request_header);
    }while(!request_header.empty());

    parse_body(msg);
}

void Request::parse_line(std::string &msg){
    size_t blank1 = msg.find_first_of(" ");
    size_t blank2 = msg.find_last_of(" ");
    headers_["method"] = msg.substr(0, blank1);
    headers_["url"] = msg.substr(blank1+1, blank2-blank1-1);
    headers_["version"] = msg.substr(blank2+1);
}

void Request::parse_header(std::string &msg){
    size_t index = msg.find_first_of(":");
    headers_[msg.substr(0, index)] = msg.substr(index+1);
}

void Request::parse_body(std::string &msg){
    ;
}

std::string Request::get_line(std::string &msg){
    size_t index = msg.find_first_of("\r\n");
    std::string res = msg.substr(0, index);
    msg = msg.substr(index+2);
    return res;
}


Response::Response() : status_code_(404),
                        file_info_(),
                        send_flag_(0){
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

void Response::set_body(std::string &body){
    if(send_flag_ != 0){
        LOG_WARN("has set body or file");
    }
    send_flag_ = 1;

    body_ = std::move(body);
    set_header("Content-Length", std::to_string(body_.size()));
}

void Response::set_file(std::string &&file_name){
    if(send_flag_ != 0){
        LOG_WARN("has set body or file");
    }
    send_flag_ = 2;

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

void Response::set_header(std::string &&key, std::string &&val){
    headers_[key] = val;
}

bool Response::is_send_file(){
    return (send_flag_ == 2);
}

Response::file_info Response::file(){
    return file_info_;
}

std::string Response::message(){
    std::string msg;
    char buf[64];

    snprintf(buf, sizeof(buf), "HTTP/1.1 %d %s\r\n", status_code_, http_status_.find(status_code_)->second.c_str());
    msg = std::string(buf);

    for (const auto& header : headers_)
    {
        snprintf(buf, sizeof(buf), "%s: %s\r\n", header.first.c_str(), header.second.c_str());
        msg += std::string(buf);
    }

    msg += "\r\n";

    if(!is_send_file()){
        msg += body_;
    }

    return msg;
}