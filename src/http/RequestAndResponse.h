#ifndef _REQUESTANDRESPONSE_
#define _REQUESTANDRESPONSE_

#include <string>
#include <vector>
#include <map>
#include <boost/noncopyable.hpp>

namespace base{

class Request : boost::noncopyable{
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

class Response : boost::noncopyable{
public:
    struct file_info{
        file_info() : file_name("./src/html/"),
                        file_size(0){
                            ;
        }

        std::string file_name;
        long int file_size;
    };

    Response();

    std::string message();

    void set_status_code(int code);

    void set_keep_alive();

    void set_content_type(std::string type);

    void set_body(std::string &body);

    void set_file(std::string &&file_name);

    bool is_send_file();

    file_info file();
private:
    void set_header(std::string &&key, std::string &&val);

    int status_code_;
    std::string body_;
    std::map<std::string, std::string> headers_;
    static const std::map<int , std::string> http_status_;
    file_info file_info_;
    int send_flag_;
};

}

#endif