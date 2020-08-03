#ifndef _REDIS_POOL_
#define _REDIS_POOL_

#include <memory>
#include <queue>
#include <map>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <boost/noncopyable.hpp>
#include <iostream>

#include "Log.h"
#include "TaskThread.h"
#include "RedisConnect.h"

namespace database{

class RedisPool : boost::noncopyable{
public:
    static RedisPool& get_instance(){
        static RedisPool instance;
        return instance;
    }
    
    std::unique_ptr<database::RedisConnect> &get_connection(){
        pid_t tid = base::TaskThread::get_tid();
        if(!conns_.count(tid)){
            std::lock_guard<std::mutex> locker(mtx_);
            if(!conns_.count(tid)){
                conns_[tid] = std::make_unique<database::RedisConnect>();
            }
        }
        return conns_[tid];
    }

private:
    RedisPool(){
        ;
    }
    ~RedisPool(){
        ;
    }

    std::mutex mtx_;
    std::map<pid_t, std::unique_ptr<database::RedisConnect>> conns_;
};

inline bool redis_update_string(std::string &key, std::string &val){
    return RedisPool::get_instance().get_connection()->update_string(key, val);
}
inline bool redis_compare_string(std::string &key, std::string &val){
    return RedisPool::get_instance().get_connection()->compare_string(key, val);
}
inline bool redis_exists_string(std::string &key){
    return RedisPool::get_instance().get_connection()->exists_string(key);
}

inline bool redis_update_set(std::string &key, std::string &val){
    return RedisPool::get_instance().get_connection()->update_set(key, val);
}
inline std::vector<std::string> redis_get_set(std::string &key){
    return RedisPool::get_instance().get_connection()->get_set(key);
}

/*          队列实现的连接池
class RedisPool : boost::noncopyable{
public:
    static RedisPool& get_instance(){
        static RedisPool instance;
        return instance;
    }

    static void set_size(int num){
        size_ = num;
    }

    database::RedisConnect *get_connection(){
        std::unique_lock<std::mutex> locker(mtx_);
        while(conns_.size() == 0){
            con_.wait(locker);
        }
        RedisConnect *conn = conns_.front();
        conns_.pop();
        std::cout<<"after get current size:"<<conns_.size()<<std::endl;
        return conn;
    }
    void free_connection(RedisConnect *conn){
        std::unique_lock<std::mutex> locker(mtx_);
        conns_.push(conn);
        con_.notify_one();
        std::cout<<"after push current size:"<<conns_.size()<<std::endl;
    }

private:
    RedisPool(){
        for(int i = 0; i < size_; i++){
            conns_.push( new database::RedisConnect(this) );
        }
    }
    ~RedisPool(){
        ;
    }

    static int size_;
    std::queue<database::RedisConnect *> conns_;
    std::condition_variable con_;
    std::mutex mtx_;
};

int RedisPool::size_ = 8;

inline bool redis_update_string(std::string &key, std::string &val){
    RedisConnect *conn = RedisPool::get_instance().get_connection();
    bool flag = conn->update_string(key, val);
    RedisPool::get_instance().free_connection(conn);
    return flag;
}
inline bool redis_compare_string(std::string &key, std::string &val){
    RedisConnect *conn = RedisPool::get_instance().get_connection();
    bool flag = conn->compare_string(key, val);
    RedisPool::get_instance().free_connection(conn);
    return flag;
}
inline bool redis_exists_string(std::string &key){
    RedisConnect *conn = RedisPool::get_instance().get_connection();
    bool flag = conn->exists_string(key);
    RedisPool::get_instance().free_connection(conn);
    return flag;
}

inline bool redis_update_set(std::string &key, std::string &val){
    RedisConnect *conn = RedisPool::get_instance().get_connection();
    bool flag = conn->update_set(key, val);
    RedisPool::get_instance().free_connection(conn);
    return flag;
}
inline std::vector<std::string> redis_get_set(std::string &key){
    RedisConnect *conn = RedisPool::get_instance().get_connection();
    std::vector<std::string> res = conn->get_set(key);
    RedisPool::get_instance().free_connection(conn);
    return res;
}
*/

}


#endif