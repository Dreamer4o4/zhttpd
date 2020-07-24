# zhttpd - multithreaded lightweight C++ Server

使用线程池与I/O多路复用(epoll)搭建的一个Reactor模式的TcpServer，one thread one loop，支持长链接,并发性能良好。    
基于TcpServer搭建了HttpServer，实现了对请求报文的解析与组装响应报文。   
目前只实现了用户的登陆与注册，使用redis来存储用户信息。

* 整个服务器几乎没有用到锁，减少了竞态的产生
* 使用sendfile来发送响应正文，减少拷贝次数，零拷贝

##  Building
安装redis       
```
sudo apt-get install redis-server
```     
安装C++的hiredis库  
```
sudo apt-get install libhiredis-dev
```     
编译
```
./mk.sh
```   

##  Runing
num表示开启多少个工作线程
```
./server num
```

* [测试信息]()    
* [代码结构]()

