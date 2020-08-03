#ifndef _REDIS_CONNECTION_
#define _REDIS_CONNECTION_

#include <hiredis/hiredis.h>
#include <string>
#include <cstring>
#include <vector>
#include <mutex>
#include <boost/noncopyable.hpp>

#include "Log.h"

namespace database{

class RedisPool;

class RedisConnect : boost::noncopyable{
public:
    RedisConnect(){
        connect();
    }
    ~RedisConnect(){
        disconnect();
    }

    bool update_string(std::string &key, std::string &val);
    bool compare_string(std::string &key, std::string &val);
    bool exists_string(std::string &key);

    bool update_set(std::string &key, std::string &val);
    std::vector<std::string> get_set(std::string &key);
private:
    void connect();
    void disconnect();
    
    class RedisReply{
    public:
        RedisReply(redisReply *reply = NULL) : reply_(reply){
            ;
        }
        ~RedisReply(){
            if(reply_ != NULL){
                freeReplyObject(reply_);
                reply_ = NULL;
            }
        }
        redisReply *reply(){
            return reply_;
        }
    private:
        redisReply *reply_;
    };

    std::mutex mtx_;
    redisContext *context_;  
};

}

#endif