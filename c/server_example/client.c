#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8181
#define IP_ADDRESS "127.0.0.1"
#define BUFSIZE 8196

pexit(char *msg) {
    perror(msg);
    exit(1);
}

main() {
    
    int i, sockfd;
    char buffer[BUFSIZE];
    static struct sockaddr_in serv_addr;

    printf("client trying to connect to %s:%d",IP_ADDRESS,PORT);
    if((sockfd=socket(AF_INET, SOCK_STREAM,0))<0) {
        pexit("socket() failed");
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    serv_addr.sin_port = htons(PORT);

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0) {
        perror("connect() failed");
    }

    write(sockfd,"GET /index.html \r\n",18);
    while((i=read(sockfd,buffer,BUFSIZE))>0) {
        write(1,buffer,i);
    }
}
