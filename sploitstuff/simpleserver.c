#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define LISTENQ 1024

int main(int argc, char ** argv)
{
  int listen_s;
  int connect_s;
  uint16_t port;
  struct sockaddr_in servaddr;
  char buffer[512];
  char *endptr;

  if(argc == 2) {
    port = atoi(argv[1]);
  } else {
    fprintf(stderr, "Invalid arguments.  You need to give a port.\n");
    exit(EXIT_FAILURE);
  }

  if((listen_s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    fprintf(stderr, "Error creating listening socket.\n");
    exit(EXIT_FAILURE);
  }
  
  memset(&servaddr, 0, sizeof(struct sockaddr_in));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(port);

  if(bind(listen_s, (struct sockaddr *)&servaddr, sizeof(struct sockaddr)) < 0) 
  {
    fprintf(stderr, "Failed to bind to listen socket.\n");
    exit(EXIT_FAILURE);
  }

  if(listen(listen_s, LISTENQ) < 0) {
    fprintf(stderr, "Failed to listen on socket.\n");
    exit(EXIT_FAILURE);
  }

  /* Loop! */

  while(1) {
    if((connect_s = accept(listen_s, NULL, NULL)) < 0) {
      fprintf(stderr, "Error accepting connection.\n");
      exit(EXIT_FAILURE);
    }

    endptr = buffer;
    while(read(connect_s, endptr, 1) == 1) {
      if(*endptr == 0 || *endptr == '\n') break;
      endptr++;
    }
    write(connect_s, "Read: ", 6);
    write(connect_s, buffer, endptr-buffer);

    if (close(connect_s) < 0) {
      fprintf(stderr, "Error calling close.\n");
      exit(EXIT_FAILURE);
    }

  }
}
