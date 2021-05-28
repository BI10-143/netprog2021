#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char const *agrv[]){
    int sockfd, clientfd;
	socklen_t clen;
	struct sockaddr_in saddr, caddr;
	unsigned short port = 8785;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0){
      	printf("Cannot create the requested socket\n");
      	exit(1);
    }
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int));
	int fl = fcntl(sockfd, F_GETFL, 0);
	fl |= O_NONBLOCK;
	fcntl(sockfd, F_SETFL, fl);

	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0){
        printf("Cannot Bind, oops\n");
        perrpr(">>bind")
        exit(1);
    }

    if (listen(sockfd, 5) < 0){
        printf("Cannot Listen\n");
        exit(1);
    }

    clen=sizeof(caddr);
    if ((clientfd = accept(sockfd, (struct sockaddr *) &caddr, &clen)) > 0){
        int fl = fcntl(clientfd, F_GETFL, 0);
		fl |= O_NONBLOCK;
		fcntl(clientfd, F_SETFL, fl);
		printf("Successfully reached to Client\n");
        while (1) {
			char sc[500];
			memset(sc, 0, 500);
			if (read(clientfd, sc, 500) > 0) {
				printf("Client>> %s\n", sc);
			}
			struct pollfd input[1] = {{.fd = 0, .events = POLLIN}};
			if (poll(input, 1, 300) > 0) {
		      	fgets(sc, 500, stdin);
			    sc[strlen(sc) - 1] = 0;
			    write(clientfd, sc, strlen(sc));
			}
		}
    }      
	return 1;
}
