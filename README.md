# zhttpd - multithreaded lightweight C++ Server

使用线程池与I/O多路复用(epoll)搭建的一个Reactor模式的TcpServer，one thread one loop，支持长链接,并发性能良好。    
基于TcpServer搭建了HttpServer，实现了对请求报文的解析与组装响应报文。   
目前实现的是类似于私人博客的功能，每个账号只能看见自己写的博客，使用redis来存储用户信息。

* 整个TCP服务器没有使用锁，减少了竞态的产生
* 使用sendfile来发送响应正文，减少拷贝次数，零拷贝
* 使用原生指针取代智能指针,减少维护引用计数的开销

已运行在云服务器上  
[网站入口](http://120.76.133.103:4000/)

##  Building
安装redis与hiredis库  
```
sudo apt-get install redis-server
sudo apt-get install libhiredis-dev
```     
编译
```
./mk.sh
```   

##  Runing
```
./server -n num -p port -h
```
-n  表示线程池大小，默认8
-p  表示服务端监听端口号，默认4000
-h  帮助

* [测试信息](https://github.com/zhgit-hub/zhttpd/blob/master/测试信息.md)    
* [代码结构](https://github.com/zhgit-hub/zhttpd/blob/master/代码结构.md)
* [性能调优](https://github.com/zhgit-hub/zhttpd/blob/master/性能调优.md)

