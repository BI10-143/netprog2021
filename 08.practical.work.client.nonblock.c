#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>


int main(int argc, char **argv) {
    struct hostent *dell;
    if (argc < 2) {
      	char hostname[1000];
      	printf("Please enter the hostname: ");
      	fgets(hostname, sizeof(hostname), stdin);
      	dell = gethostbyname(hostname);
    }
    else {
      	dell = gethostbyname(argv[1]);
    }

    if (dell == NULL) {
       	printf("Failed to connect\n");
    } else {
    	printf("%s: ", dell->h_name);
       	unsigned int i = 0;
       	while ( dell -> h_addr_list[i] != NULL) {
          	printf( "%s\n ", inet_ntoa( *( struct in_addr*)(dell -> h_addr_list[i])));
          	i++;
       	}
       	printf("\n");
    }

    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
      	printf("Error creating socket sad\n");
      	exit(1);
    }
  
    struct sockaddr_in saddr;
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    memcpy((char *) &saddr.sin_addr.s_addr, dell->h_addr_list[0], dell->h_length);
    saddr.sin_port = htons(8785);
    if (connect(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0) {
        printf("Cannot connect sadly\n");
        perror("Connect");
        exit(1);
    }
    int fl = fcntl(clientfd, F_GETFL, 0);
	fl |= O_NONBLOCK;
	fcntl(clientfd, F_SETFL, fl);
    printf("Successfully connected to server. Have fun!\n");

    while (1) {
        char sc[500];
        memset(sc, 0, 500);
        if (strcmp(sc, "/quit") == 0) {
	      	print("Server>>\n", sc);
        }
        struct pollfd input[1] = {{.fd = 0, .events = POLLIN}};
			if (poll(input, 1, 300) > 0) {
		    	fgets(sc, 500, stdin);
			  	sc[strlen(sc) - 1] = 0;
			  	write(clientfd, sc, strlen(sc));
			    }
        

    }
}