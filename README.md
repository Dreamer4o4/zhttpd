# zhttpd
refer to muduo      
one loop one thread     


# bench result  
cmd:           
ab -n 100000 -r -k -c 1000 127.0.0.1:4000/        
```
This is ApacheBench, Version 2.3 <$Revision: 1843412 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking 127.0.0.1 (be patient)
Completed 10000 requests
Completed 20000 requests
Completed 30000 requests
Completed 40000 requests
Completed 50000 requests
Completed 60000 requests
Completed 70000 requests
Completed 80000 requests
Completed 90000 requests
Completed 100000 requests
Finished 100000 requests


Server Software:        zhttp
Server Hostname:        127.0.0.1
Server Port:            4000

Document Path:          /
Document Length:        82 bytes

Concurrency Level:      1000
Time taken for tests:   1.896 seconds
Complete requests:      100000
Failed requests:        0
Keep-Alive requests:    100000
Total transferred:      18500000 bytes
HTML transferred:       8200000 bytes
Requests per second:    52745.18 [#/sec] (mean)
Time per request:       18.959 [ms] (mean)
Time per request:       0.019 [ms] (mean, across all concurrent requests)
Transfer rate:          9529.16 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    0   2.4      0      25
Processing:     4   19   1.7     18      43
Waiting:        0   19   1.7     18      43
Total:          4   19   3.4     18      49

Percentage of the requests served within a certain time (ms)
  50%     18
  66%     19
  75%     19
  80%     19
  90%     20
  95%     20
  98%     23
  99%     43
 100%     49 (longest request)

```