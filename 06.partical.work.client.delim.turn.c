#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *agrv[]){
    int sockfd, clen, clientfd;
    struct sockaddr_in saddr, caddr;
    unsigned short port = 8784;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) 
    {
      	printf("Cannot create the requested socket\n");
      	exit(1);
    }

memset(&saddr, 0, sizeof(saddr));
saddr.sin_family = AF_INET;
saddr.sin_addr.s_addr = htonl(INADDR_ANY);
saddr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0){
        printf("Cannot Bind, oops\n");
        perrpr(">>bind")
        exit(1);
    }

    if (listen(sockfd, 5) < 0) {
        printf("Cannot Listen\n");
        exit(1);
    }

    clen=sizeof(caddr);
    if ((clientfd = accept(sockfd, (struct sockaddr *) &caddr, &clen)) < 0){
        printf("Cannot accept the connection\n");
        exit(1);
    }

    void chat(int sockfd){ 
    char buff[500]; 
    char msg[500] = ""; 
    char delimiter[2] = "\n"; 
    int n = 0; 

    while(1){   
        bzero(buff, sizeof(buff)); 
        printf("Client>> ");
        fgets(buff, sizeof(buff), stdin);
        send(sockfd, &buff[n], sizeof(buff), 0);
        
        if(strncmp("Exit", buff, 2) == 0){ 
            printf("Client Exiting...\n"); 
            break; 
        }

        bzero(buff, sizeof(buff)); 
        printf("Server>> ");

        while(strcmp(&buff[n], delimiter) != 0){
            recv(sockfd, &buff[n], sizeof(buff[n]), 0); 
            printf("%c", buff[n]);
            strcat(msg, &buff[n]);
        }

        if(strncmp("Exit", msg, 4) == 0){ 
            printf("Client Exiting...exit\n"); 
            break; 
        }
    } 
} 
}

