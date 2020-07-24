#ifndef _DATA_
#define _DATA_

#include <netdb.h>
#include <string>
#include <cstring>

namespace base{

struct data{
    data(){
        memset(client_host, 0, sizeof(client_host));
        memset(client_port, 0, sizeof(client_port));
        strcpy(client_host, "unknow");
        strcpy(client_port, "unknow");
    }

    data(const char* host, const char* port){
        memset(client_host, 0, sizeof(client_host));
        memset(client_port, 0, sizeof(client_port));
        strcpy(client_host, host);
        strcpy(client_port, port);
    }

    data(const data &info){
        memset(client_host, 0, sizeof(client_host));
        memset(client_port, 0, sizeof(client_port));
        strcpy(client_host, info.client_host);
        strcpy(client_port, info.client_port);
    }

    data & operator =(const data &info){
        memset(client_host, 0, sizeof(client_host));
        memset(client_port, 0, sizeof(client_port));
        strcpy(client_host, info.client_host);
        strcpy(client_port, info.client_port);
        return *this;
    }

    char client_host[NI_MAXHOST];
    char client_port[NI_MAXSERV];

};

}

#endif