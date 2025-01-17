#include <stdio.h>
#include <netdb.h>
#include <sys/client.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


int main(int argc, char *argv) {
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
    saddr.sin__family = AF_INET;
    memcpy((char *) &saddr.sin__addr.s_addr, dell->h_addr_list[0], dell->h_length);
    saddr.sin__port = htons(8785);
    if (connect(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0) {
        printf("Cannot connect sadly\n");
        perror("Connect");
    }
    printf("Successfully connected to server. Have fun!\n");

}