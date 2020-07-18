#include <iostream>
#include <string>

#include "Log.h"

using namespace base;

void Log::write(int level, std::string file, std::string func, int line, std::string &msg){
    std::string log(Time::get_now_time());

    if(level == INFO){
        log.append("[INFO] ");
    }else if(level == WARN){
        log.append("[WARN] ");
    }else if(level == ERROR){
        log.append("[ERROR] ");
    }

    log.append("filename:"+file+" ");
    log.append("function:"+func+" ");
    log.append("line:"+std::to_string(line)+"\n");

    log.append(msg+"\n");

    std::cout<<log<<std::endl;
}

void Log::write(int level, std::string file, std::string func, int line, std::string &&msg){
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