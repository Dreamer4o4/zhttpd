#ifndef _REQUESTANDRESPONSE_
#define _REQUESTANDRESPONSE_

#include <string>
#include <vector>
#include <map>
#include <boost/noncopyable.hpp>


namespace base{

class Request : boost::noncopyable{
public:
    enum Equal{
        FALSE,
        ALMOST,
        EQUAL
    };

    Request(std::string &req);

    int method_equal(std::string &&val);
    int url_equal(std::string &&val);
    int version_equal(std::string &&val);
    int connection_equal(std::string &&val);

    std::string get_body();
    std::string get_cookie();
private:
    int equal(std::string &&key, std::string &&val);

    void parse(std::string &msg);
    void parse_line(std::string &msg);
    void parse_header(std::string &msg);
    void parse_cookie();
    void parse_body(std::string &msg);
    
    std::string get_line(std::string &msg);

    std::map<std::string, std::string> headers_;
    std::map<std::string, std::string> cookies_;
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

    enum SendFlag{
        NONE,
        BODY,
        FILE
    };

    Response();

    std::string message();

    void set_status_code(int code);
    void set_keep_alive();
    void set_content_type(std::string &&type);
    void set_body(std::string &body);
    void set_file(std::string &&file_name);

    void set_cookie_username(std::string &val);
    void set_cookie_password(std::string &val);

    bool is_send_file();

    file_info file();
private:
    void set_header(std::string &&key, std::string &&val);
    void set_cookie(std::string &&key, std::string &&val);

    int status_code_;
    std::string body_;
    std::map<std::string, std::string> headers_;
    std::map<std::string, std::string> cookies_;
    static const std::map<int , std::string> http_status_;
    file_info file_info_;
    int send_flag_;
};

}

#endif