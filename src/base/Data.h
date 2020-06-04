#ifndef _DATA_
#define _DATA_

#include <netdb.h>
#include <string>
#include <cstring>

namespace base{

struct data{
    data(int fd_) : fd(fd_){
        // memset(client_host, 0, sizeof(client_host));
        // memset(client_server, 0, sizeof(client_server));
        strcpy(client_host, "unknow321");
        strcpy(client_server, "unknow123");
    }

    int fd;
    char client_host[NI_MAXHOST];
    char client_server[NI_MAXSERV];

};

}

#endif