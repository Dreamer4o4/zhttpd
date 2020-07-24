#include <iostream>
#include <string>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "Log.h"

using namespace base;

void Log::write(int level, std::string file, std::string func, int line, const char *msg, ...){
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


    va_list args;
    char s[100];
    memset(s, 0, sizeof(s));

    va_start(args, msg);
    vsprintf(s, msg, args);
    va_end(args);

    log.append(std::string(s)+"\n");

    std::cout<<log<<std::endl;
}