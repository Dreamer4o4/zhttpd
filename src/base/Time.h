#ifndef _TIME_
#define _TIME_

#include <boost/noncopyable.hpp>
#include <string>
#include <ctime>

namespace base{

class Time : boost::noncopyable{
    public:
        static std::string get_now_time(){
            time_t now = std::time(NULL);
            return std::string(ctime(&now));
        }
    private:


};

}

#endif