#ifndef _REQUESTANDRESPONSE_
#define _REQUESTANDRESPONSE_

#include <string>
#include <vector>
#include <map>

namespace base{

class Request{
public:
    Request(std::string &req);

#define method_equal(val)   equal("method", val)   
#define version_equal(val)  equal("version", val)

private:
    bool equal(std::string &&key, std::string &&val);

    void parse(std::string &msg);

    void parse_line(std::string &msg);

    void parse_header(std::string &msg);

    void parse_body(std::string &msg);
    
    std::string get_line(std::string &msg);

    std::map<std::string, std::string> headers_;
};

class Response{
public:
    Response();

    std::string message();

    void set_status_code(int code);

    void set_keep_alive();

    void set_content_type(std::string type);

    void set_body(std::string &body);
private:
    void set_header(std::string &&key, std::string &&val);

    int status_code_;
    std::string body_;
    std::map<std::string, std::string> headers_;
};

}

#endif