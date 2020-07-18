#include <sys/epoll.h>
#include <queue>
#include <vector>
#include <memory>
#include <cstring>

#include "Epoll.h"
#include "Log.h"
#include "Channel.h"


using namespace base;

Epoll::Epoll() : epfd_(epoll_create1(EPOLL_CLOEXEC)),
                    events_(events_size){
    if(epfd_ < 0){
        LOG_ERROR("epoll create failed");
    }
}

Epoll::~Epoll(){
    close(epfd_);
}

bool Epoll::add_event(std::shared_ptr<Channel> &channel){
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = channel->event();
    ev.data.ptr = channel.get();
    
    return (epoll_ctl(epfd_, EPOLL_CTL_ADD, channel->fd(), &ev) == 0) ? true : false;
}

bool Epoll::rm_event(std::shared_ptr<Channel> &channel){
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));

    return (epoll_ctl(epfd_, EPOLL_CTL_DEL, channel->fd(), &ev) == 0) ? true : false;
}

int Epoll::wait(int time, ChannelList &channels){
    int num = epoll_wait(epfd_, &*events_.begin(), static_cast<int>(events_.size()), time);

    if(num > 0){
        for(int i=0; i<num; i++){
            Channel *channel = static_cast<Channel*>(events_[i].data.ptr);
            channel->set_revents(events_[i].events);
            channels.push_back(channel->shared_from_this());
        }

        if (static_cast<size_t>(num) == events_.size()){
            events_.resize(events_.size()*2);
        }

    }

    return num;
}

