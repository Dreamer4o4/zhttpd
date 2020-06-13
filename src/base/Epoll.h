#ifndef _EPOLL_
#define _EPOLL_

#include <boost/noncopyable.hpp>
#include <sys/epoll.h>
#include <cstring>
#include <memory>
#include <vector>
#include <queue>
#include <iostream>

#include "Log.h"
#include "BlockingQueue.h"

namespace base{

class Epoll : boost::noncopyable{
    public:
        enum Type{
            LT,
            ET
        };

        Epoll() : epfd_(epoll_create1(EPOLL_CLOEXEC)),
                    events_(events_size){
            if(epfd_ < 0){
                LOG_ERROR("epoll create failed");
            }
        }

        ~Epoll(){
            close(epfd_);
        }

        bool add_event(int &fd, int type){
            struct epoll_event ev;
            memset(&ev, 0, sizeof(ev));
            if(type == LT){
                ev.events = EPOLLIN;
            }else{
                ev.events = EPOLLIN | EPOLLET;
            }
            ev.data.fd = fd;
            
            return (epoll_ctl(epfd_, EPOLL_CTL_ADD, fd, &ev) == 0) ? true : false;
        }

        bool rm_event(int fd){
            struct epoll_event ev;
            memset(&ev, 0, sizeof(ev));

            return (epoll_ctl(epfd_, EPOLL_CTL_DEL, fd, &ev) == 0) ? true : false;
        }

        int wait(int time, std::queue<int> &que){
            int num = epoll_wait(epfd_, &*events_.begin(), static_cast<int>(events_.size()), time);

            if(num > 0){
                for(int i=0; i<num; i++){
                    if((events_[i].events & EPOLLIN)){
                        que.push(events_[i].data.fd);
                    }
                }

                if (static_cast<size_t>(num) == events_.size()){
                    events_.resize(events_.size()*2);
                }

            }

            return num;
        }

        /*
        **  only for acceptor
        */
        int wait(int time, int fd){
            int num = epoll_wait(epfd_, &*events_.begin(), static_cast<int>(events_.size()), time);

            if(num > 0){
                for(int i=0; i<num; i++){
                    if((events_[i].events & EPOLLIN) && (events_[i].data.fd == fd)){
                        return 1;
                    }
                }
            }

            return 0;
        }

    private:
        static const int events_size = 16;

        int epfd_;
        std::vector<struct epoll_event> events_;
};

}

#endif