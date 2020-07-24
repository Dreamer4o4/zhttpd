#include <cstdio>
#include <iostream>

#include "RequestAndResponse.h"

using namespace base;

static std::map<int , std::string> http_status{
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


Response::Response() : status_code_(404){
    set_header("Server", "zhttp");
    set_header("Connection", "Close");
    set_header("Content-Type", "text/html");
}

void Response::set_keep_alive(){
    set_header("Connection", "Keep-Alive");
}

void Response::set_status_code(int code){
    status_code_ = code;
}

void Response::set_body(std::string &body){
    body_ = std::move(body);
    set_header("Content-Length", std::to_string(body_.size()));
}

void Response::set_header(std::string &&key, std::string &&val){
    headers_[key] = val;
}

std::string Response::message(){
    std::string msg;
    char buf[64];

    snprintf(buf, sizeof(buf), "HTTP/1.1 %d %s\r\n", status_code_, http_status[status_code_].c_str());
    msg = std::string(buf);

    for (const auto& header : headers_)
    {
        snprintf(buf, sizeof(buf), "%s: %s\r\n", header.first.c_str(), header.second.c_str());
        msg += std::string(buf);
    }

    msg += "\r\n";
    msg += body_;

    return msg;
}