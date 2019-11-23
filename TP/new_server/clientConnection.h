#ifndef _CLIENT_CONNECTION_H_
#define _CLIENT_CONNECTION_H_

int receive(int fd, char *buffer, int size);
int serve(int port);

#endif