//
//  main.cpp
//  socket-server
//
//  Created by t1mkeeper on 3/11/20.
//  Copyright © 2020 t1mkeeper. All rights reserved.
//

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXLINE 4096

int main(int argc, char** argv){
    int  listenfd, connfd;
    struct sockaddr_in  servaddr;
    char  buff[4096];
    int  n;

    if( (listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1 ){
        printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
        return 0;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(8878);

    int ret = bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if( ret == -1){
        printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
        return 0;
    }
    

    ret = listen(listenfd, 10);
    if( ret == -1){
        printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
        return 0;
    }
    

    printf("======waiting for client's request======\n");
    while(1){
//        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
        if( connfd == -1){
            printf("accept socket error: %s(errno: %d) \n",strerror(errno),errno);
            continue;
        }
        
        n = recv(connfd, buff, MAXLINE, 0);
        buff[n] = '\0';
        printf("recv msg from client: %s\n", buff);
        close(connfd);
    }
    close(listenfd);
    return 0;
}
