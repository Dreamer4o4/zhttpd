#ifndef _LOG_
#define _LOG_

#include <boost/noncopyable.hpp>
#include <cstdlib>

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
        
        void write(int level, std::string file, std::string func, int line, const char *msg, ...);
        
    private:
        Log() = default;
    
        ~Log() = default;
};

#define LOG_INFO(msg, ...)   base::Log::get_instance().write(base::Log::INFO, __FILE__, __FUNCTION__, __LINE__, msg, ##__VA_ARGS__)
#define LOG_WARN(msg, ...)   base::Log::get_instance().write(base::Log::WARN, __FILE__, __FUNCTION__, __LINE__, msg, ##__VA_ARGS__)
#define LOG_ERROR(msg, ...)   {base::Log::get_instance().write(base::Log::ERROR, __FILE__, __FUNCTION__, __LINE__, msg, ##__VA_ARGS__);std::exit(0);}

}

#endif