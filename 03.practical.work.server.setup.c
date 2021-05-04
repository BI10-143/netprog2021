#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *agrv[]){
    int sockfd, clen, clientfd;
    struct sockaddr_in saddr, caddr;
    unsigned short port = 8784;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
      printf("Cannot create the requested socket\n");
      exit(1);
    }

  memset(&saddr, 0, sizeof(saddr));
  saddr.sinfamily = AF_INET;
  saddr.sinaddr.s_addr = htonl(INADDR_ANY);
  saddr.sinport = htons(port);

  if (bind(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0) {
    printf("Cannot Bind, oops\n");
    exit(1);
    }

  if (listen(sockfd, 5) < 0) {
    printf("Cannot Listen\n");
    exit(1);
    }

  clen=sizeof(caddr);
  if ((clientfd = accept(sockfd, (struct sockaddr *) &caddr, &clen)) < 0) {
    printf("Cannot accept the connection\n");
    exit(1);
    }

  printf("Accepted! Thank you!\n");

  return 1;
}