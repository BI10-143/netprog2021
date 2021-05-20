#include <stdio.h>
#include <netdb.h>
#include <sys/client.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>


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
       	unsigned int i=0;
       	while ( dell -> h_addr_list[i] != NULL) {
          	printf( "%s\n ", inet_ntoa( *( struct in_addr*)( dell -> h_addr_list[i])));
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
    saddr.sinfamily = AF_INET;
    memcpy((char *) &saddr.sin__addr.s_addr, dell->h_addr_list[0], dell->h_length);
    saddr.sinport = htons(8785);
    if (connect(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0) {
        printf("Cannot connect sadly\n");
        perror("Connect");
    }
    printf("Successfully connected to server. Have fun!\n");

    while (1) {
        char sc[500];
        memset(sc, 0, 500);
        printf("Client>>");
        fgets(sc, 500, stdin);
        write(sockfd, sc, strlen(sc));

        read(sockfd, s, 500);
        sc[strlen(sc) -1] = 0;
        printf("Server>> %s\n", sc);
    }

}
void chat(int sockfd){ 
    char buff[500]; 
    char msg[500] = ""; 
    char delimiter[2] = "\n"; 
    int n = 0; 

    while(1){   
        bzero(buff, sizeof(buff)); 
        printf("Server">> ");
        fgets(buff, sizeof(buff), stdin);
        send(sockfd, &buff[n], sizeof(buff), 0);
        
        if(strncmp("Exit", buff, 2) == 0) { 
            printf("Server Exiting...\n"); 
            break; 
        }

        bzero(buff, sizeof(buff)); 
        printf("Client>> ");

        while(strcmp(&buff[n], delimiter) != 0){
            recv(sockfd, &buff[n], sizeof(buff[n]), 0); 
            printf("%c", buff[n]);

            strcat(msg, &buff[n]);
        }

        if(strncmp("Exit", msg, 4) == 0) { 
            printf("Server Exiting...exit\n"); 
            break; 
        }
    } 
} 
