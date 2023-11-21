#include<winsock2.h>
#include<stdio.h>
#include<stdlib.h>
#include<WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")

int main(int argc, char *argv[]){
    // Инициализация сокетов
    WSADATA wsaData;
    int rc = WSAStartup(MAKEWORD(2,2),&wsaData);

    if (rc != 0){
        fprintf(stderr,"Error during socket's initializing\n");
        return 1;
    }
    // Создание сокета
    SOCKET sockListen;
    sockListen = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if (sockListen == INVALID_SOCKET){
        fprintf(stderr,"Error during socket's creating\n");
        return 1;
    }

    // Инициализация параметров соединения для сокета
    SOCKADDR_IN sockParams;
    //memset(&sockListen,0,sizeof(sockListen));
    sockParams.sin_family = AF_INET;
    sockParams.sin_port = htons(8005);
    sockParams.sin_addr.S_un.S_addr = INADDR_ANY; 

    // При попытке соединения...
    if(bind(sockListen,(SOCKADDR*)&sockParams,sizeof(sockParams))==SOCKET_ERROR){
        fprintf(stderr,"Error during socket's binding\n");
        return 1;
    }

    if (listen(sockListen,100)==SOCKET_ERROR){
        fprintf(stderr,"Error during socket's listening\n");
        return 1;
    }

    SOCKET clSocket;
    SOCKADDR_IN clIp;

    int clIpSize = sizeof(clIp);
    
    while (1==1){
        clSocket = accept(sockListen,(SOCKADDR*)&clIp,&clIpSize);
        if (clSocket ==INVALID_SOCKET){
            fprintf(stderr,"accepting failure\n");
            return 1;
        } else{
            fprintf(stdout,"success\n");

            // char output[64];
            // inet_pton(AF_INET, output, &clIp.sin_addr);
            // fprintf(stdout,"%s\n",output);
        }    
    }

    return 0;
}