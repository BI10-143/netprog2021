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

    printf("Accepted! Thank you!\n");
    while (1) {
        char sc[500];
        memset(sc, 0, 500);
        read(sockfd, s, 500);
        sc[strlen(sc) -1] = 0
        printf("Client>> %s\n", sc);

        printf("Server>>");
        fgets(sc, 500, stdin);
        write(sockfd, sc, strlen(sc));

    }

	return 1;
}
