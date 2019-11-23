#include "clientConnection.h"
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

int serve(int port) {
    int fd, serverFd;
    int result;
    struct sockaddr_in serv_addr;

    bzero((char *) &serv_addr, sizeof(serv_addr));
    port = htons(port);
    
    serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFd == -1) {
        perror("socket error");
        exit(1);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = port;

    int enable = 1;
    result = setsockopt(serverFd, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(enable));
    if (result == -1) {
        perror("setsockopt error");
        exit(1);
    }
    
    result = bind(serverFd,(struct sockaddr *)&serv_addr,0x10);
    if (result == -1) {
        perror("bind error");
        exit(1);
    }
    
    result = listen(serverFd,1);
    if (result == -1) {
        perror("listen error");
        exit(1);
    }

    fd = accept(serverFd,(struct sockaddr *)0x0,(socklen_t *)0x0);
    if (fd == 0xffffffff) {
        perror("accept error");
        exit(1);
    }

    return fd;
}

int receive(int fd, char *buffer, int size) {
  int result;
  
  result = recv(fd, buffer, size - 1, 0);
  if (result == -1) {
    perror("recv error");
    exit(1);
  }
  if (result == 0) {
    exit(0);
  }
  buffer[result] = '\0';

  return result;
}
