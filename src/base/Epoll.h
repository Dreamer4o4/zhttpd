#ifndef _EPOLL_
#define _EPOLL_

#include <boost/noncopyable.hpp>
#include <vector>
#include <queue>


namespace base{

class Channel;

class Epoll : boost::noncopyable{
    private:
        typedef std::vector<Channel*> ChannelList;

    public:
        enum Type{
            LT,
            ET
        };

        Epoll();

        ~Epoll();

        bool add_event(Channel *channel);

        bool rm_event(Channel *channel);

        int wait(int time, ChannelList &channels);

    private:
        static const int events_size = 16;

        int epfd_;
        std::vector<struct epoll_event> events_;
};

}

#endif