#include <unistd.h>
#include <iostream>
#include <functional>
#include <string>

#include "BlogServer.h"
#include "RedisPool.h"
#include "Log.h"

std::string port("4000");       //监听端口
int th_num = 8;                 //线程池大小

void parse_parameter(int argc, char *argv[]){
    int i;
    while((i = getopt(argc, argv, "hn:p:")) != EOF)
	{
		switch(i)
		{
			case 'n':
				th_num = atoi(optarg);
				break;
			case 'p':
				port = std::string(optarg);
				break;
            case 'h':
                std::cout<<"h : help"<<std::endl;
                std::cout<<"n : the size of thread pool"<<std::endl;
                std::cout<<"p : the port server listen to"<<std::endl;
                exit(0);
			default:
				break;
		}
	}
}

void test(){            //测试用例
    LOG_INFO("testing");

    // std::string key("asdasd"), val1("asdasd"), val2("1231231");
    // database::RedisTool::get_instance().update_set(key, val1);
    // database::RedisTool::get_instance().update_set(key, val2);
    // std::vector<std::string> res = database::RedisTool::get_instance().get_set(key);
    // for(auto i : res){
    //     std::cout<<i<<std::endl;
    // }

    std::string usr("zh"), val("123123");
    for(;;){
        database::redis_compare_string(usr, val);
    }

    while(1);
}


int main(int argc, char *argv[]){

    // test();

    parse_parameter(argc, argv);

    BlogServer server(port, th_num);
    server.start();

    return 0;
}