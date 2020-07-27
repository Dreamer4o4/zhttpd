#ifndef _REDIS_TOOL_
#define _REDIS_TOOL_

#include <hiredis/hiredis.h>
#include <memory>
#include <string>
#include <cstring>
#include <vector>
#include <boost/noncopyable.hpp>

#include "Log.h"

namespace database{

class RedisTool : boost::noncopyable{
public:
    static RedisTool& get_instance(){
        static RedisTool instance;
        return instance;
    }

    bool update_string(std::string &key, std::string &val){
        RedisReply reply_(static_cast<redisReply *>(redisCommand(context_, "SET %s %s", key.c_str(), val.c_str())));
        if(!reply_.reply()){
            LOG_ERROR("redis reply_ err : %d", context_->err);
            return false;
        }
        if(reply_.reply()->type == REDIS_REPLY_STATUS && (strcasecmp(reply_.reply()->str,"OK") == 0)){
            return true;
        }else{
            return false;
        }
    }

    bool compare_string(std::string &key, std::string &val){
        RedisReply reply_(static_cast<redisReply *>(redisCommand(context_, "GET %s", key.c_str())));
        if(!reply_.reply()){
            LOG_ERROR("redis reply_ err : %d", context_->err);
            return false;
        }
        if(reply_.reply()->type == REDIS_REPLY_STRING && std::string(reply_.reply()->str) == val){
            return true;
        }
        return false;
    }

    bool exists_string(std::string &key){
        RedisReply reply_(static_cast<redisReply *>(redisCommand(context_, "EXISTS %s", key.c_str())));
        if(!reply_.reply()){
            LOG_ERROR("redis reply_ err : %d", context_->err);
            return false;
        }
        if(reply_.reply()->type == REDIS_REPLY_INTEGER && reply_.reply()->integer == 1){
            return true;
        }
        return false;
    }

    bool update_set(std::string &key, std::string &val){
        RedisReply reply_(static_cast<redisReply *>(redisCommand(context_, "SADD %s %s", key.c_str(), val.c_str())));
        if(!reply_.reply()){
            LOG_ERROR("redis reply_ err : %d", context_->err);
            return false;
        }
        if(reply_.reply()->type == REDIS_REPLY_INTEGER && reply_.reply()->integer == 1){
            return true;
        }else{
            return false;
        }
    }

    std::vector<std::string> get_set(std::string &key){
        std::vector<std::string> res;
        RedisReply reply_(static_cast<redisReply *>(redisCommand(context_, "SMEMBERS %s", key.c_str())));
        if(!reply_.reply()){
            LOG_ERROR("redis reply_ err : %d", context_->err);
        }
        if(reply_.reply()->type == REDIS_REPLY_ARRAY && reply_.reply()->elements > 0){
            for(size_t i = 0; i < reply_.reply()->elements; i++){
                res.push_back(std::string(reply_.reply()->element[i]->str));
            }
        }
        return res;
    }
private:
    RedisTool(){
        connect();
    }
    ~RedisTool(){
        disconnect();
    }

    void connect(){
        timeval tv = {1, 0};
        context_ = redisConnectWithTimeout("localhost", 6379, tv);
        if(!context_){
            LOG_ERROR("connect redis failed");
        }else{
            LOG_INFO("redis connected");
        }
    }
    void disconnect(){
        if(context_){
            redisFree(context_);
            context_ = NULL;
        }
    }

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

    redisContext *context_;    
};

inline bool redis_update_string(std::string &key, std::string &val){
    return RedisTool::get_instance().update_string(key, val);
}
inline bool redis_compare_string(std::string &key, std::string &val){
    return RedisTool::get_instance().compare_string(key, val);
}
inline bool redis_exists_string(std::string &key){
    return RedisTool::get_instance().exists_string(key);
}

inline bool redis_update_set(std::string &key, std::string &val){
    return RedisTool::get_instance().update_set(key, val);
}
inline std::vector<std::string> redis_get_set(std::string &key){
    return RedisTool::get_instance().get_set(key);
}

}


#endif