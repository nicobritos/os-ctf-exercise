#ifndef _CLIENT_CONNECTION_H
#define _CLIENT_CONNECTION_H

int serve(int port);
int receive(int fd, char *buffer, int size);

#endif
