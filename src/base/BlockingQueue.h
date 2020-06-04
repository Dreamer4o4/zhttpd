#ifndef _BLOCKINGQUEUE_
#define _BLOCKINGQUEUE_

#include <boost/noncopyable.hpp>
#include <deque>
#include <mutex>
#include <condition_variable>

namespace base{

template<typename T>
class BlockingQueue : boost::noncopyable{
    public:
        BlockingQueue() : queue_(){
            ;
        }

        void push(const T &t){
            {
                std::unique_lock<std::mutex> lock(mutex_);
                queue_.push_back(t);
            }
            cond_.notify_one();
        }

        void push(T &&t){
            {
                std::unique_lock<std::mutex> lock(mutex_);
                queue_.push_back(std::move(t));
            }
            cond_.notify_one();
        }

        T pop(){
            std::unique_lock<std::mutex> lock(mutex_);
            while(queue_.empty()){
                cond_.wait(lock);
            }
            T front( std::move(queue_.front()) );
            queue_.pop_front();
            return front;
        }

        size_t size(){
            std::unique_lock<std::mutex> lock(mutex_);
            return queue_.size();
        }

    private:

        std::deque<T> queue_;
        std::mutex   mutex_;
        std::condition_variable cond_;
};

}

#endif