#ifndef _LOG_
#define _LOG_

#include <boost/noncopyable.hpp>
#include <iostream>
#include <string>
#include <cstdio>

#include "Time.h"

namespace base{

class Log : boost::noncopyable{
    public:
        enum Level{
            INFO,
            WARN,
            ERROR
        };

        static Log &get_instance(){
            static Log instance;
            return instance;
        }
        
        void write(int level, std::string file, int line, std::string &msg){
            std::string log(Time::get_now_time());

            if(level == INFO){
                log.append("[INFO] ");
            }else if(level == WARN){
                log.append("[WARN] ");
            }else if(level == ERROR){
                log.append("[ERROR] ");
            }

            log.append("filename:"+file+" ");
            log.append("line:"+std::to_string(line)+"\n");

            log.append(msg+"\n");

            std::cout<<log<<std::endl;
        }
        
        void write(int level, std::string file, int line, std::string &&msg){
            std::string log(Time::get_now_time());

            if(level == INFO){
                log.append("[INFO] ");
            }else if(level == WARN){
                log.append("[WARN] ");
            }else if(level == ERROR){
                log.append("[ERROR] ");
            }

            log.append("filename:"+file+" ");
            log.append("line:"+std::to_string(line)+"\n");

            log.append(msg+"\n");

            std::cout<<log<<std::endl;
        }

    private:
        Log() = default;
        ~Log() = default;
};

#define LOG_INFO(msg)   base::Log::get_instance().write(base::Log::INFO, __FILE__, __LINE__, msg)
#define LOG_WARN(msg)   base::Log::get_instance().write(base::Log::WARN, __FILE__, __LINE__, msg)
#define LOG_ERROR(msg)   base::Log::get_instance().write(base::Log::ERROR, __FILE__, __LINE__, msg)

}

#endif