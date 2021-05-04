#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {
    struct hostent *dell;
    if (argc < 2) {
      char host[1000];
      printf("Please enter the hostname: ");
      scanf("%s", host)
      dell = gethostbyname(host);
    }
    else {
      dell = gethostbyname(argv[1]);
    }

    if (dell == NULL) {
       printf("gethostbyname() failed to locate\n");
    } else {
       printf("%s: \n", dell->h_name);
       unsigned int i=0;
       while ( dell -> h_addr_list[i] != NULL) {
          printf( "%s ", inet_ntoa( *( struct in_addr*)( dell -> h_addr_list[i]))); 
		  i++;
       }
       printf("\n");
    }

}
