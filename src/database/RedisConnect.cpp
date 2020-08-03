#include "RedisConnect.h"

using namespace database;

bool RedisConnect::update_string(std::string &key, std::string &val){
    std::lock_guard<std::mutex> locker(mtx_);
    RedisReply reply_(static_cast<redisReply *>(redisCommand(context_, "SET %s %s", key.c_str(), val.c_str())));
    if(!reply_.reply()){
        LOG_WARN("redis reply_ err : %d", context_->err);
        return false;
    }
    if(reply_.reply()->type == REDIS_REPLY_STATUS && (strcasecmp(reply_.reply()->str,"OK") == 0)){
        return true;
    }else{
        return false;
    }
}

bool RedisConnect::compare_string(std::string &key, std::string &val){
    std::lock_guard<std::mutex> locker(mtx_);
    RedisReply reply_(static_cast<redisReply *>(redisCommand(context_, "GET %s", key.c_str())));
    if(!reply_.reply()){
        LOG_WARN("redis reply_ err : %d", context_->err);
        return false;
    }
    if(reply_.reply()->type == REDIS_REPLY_STRING && std::string(reply_.reply()->str) == val){
        return true;
    }
    return false;
}

bool RedisConnect::exists_string(std::string &key){
    std::lock_guard<std::mutex> locker(mtx_);
    RedisReply reply_(static_cast<redisReply *>(redisCommand(context_, "EXISTS %s", key.c_str())));
    if(!reply_.reply()){
        LOG_WARN("redis reply_ err : %d", context_->err);
        return false;
    }
    if(reply_.reply()->type == REDIS_REPLY_INTEGER && reply_.reply()->integer == 1){
        return true;
    }
    return false;
}

bool RedisConnect::update_set(std::string &key, std::string &val){
    std::lock_guard<std::mutex> locker(mtx_);
    RedisReply reply_(static_cast<redisReply *>(redisCommand(context_, "SADD %s %s", key.c_str(), val.c_str())));
    if(!reply_.reply()){
        LOG_WARN("redis reply_ err : %d", context_->err);
        return false;
    }
    if(reply_.reply()->type == REDIS_REPLY_INTEGER && reply_.reply()->integer == 1){
        return true;
    }else{
        return false;
    }
}

std::vector<std::string> RedisConnect::get_set(std::string &key){
    std::lock_guard<std::mutex> locker(mtx_);
    std::vector<std::string> res;
    RedisReply reply_(static_cast<redisReply *>(redisCommand(context_, "SMEMBERS %s", key.c_str())));
    if(!reply_.reply()){
        LOG_WARN("redis reply_ err : %d", context_->err);
    }
    if(reply_.reply()->type == REDIS_REPLY_ARRAY && reply_.reply()->elements > 0){
        for(size_t i = 0; i < reply_.reply()->elements; i++){
            res.push_back(std::string(reply_.reply()->element[i]->str));
        }
    }
    return res;
}

void RedisConnect::connect(){
    timeval tv = {1, 0};
    context_ = redisConnectWithTimeout("localhost", 6379, tv);
    if(!context_){
        LOG_WARN("connect redis failed");
    }else{
        // LOG_INFO("redis connected");
    }
}

void RedisConnect::disconnect(){
    if(context_){
        redisFree(context_);
        context_ = NULL;
    }
}