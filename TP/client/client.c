#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>

#define ERROR_NO 0
#define ERROR_SOCKET_OPEN 1
#define ERROR_CONNECT 2
#define ERROR_FORK 2

#define LOCALHOST "0.0.0.0"
#define BUFFER_SIZE 1024
#define PORT 23423

int main(int argc, char *argv[]) {
	struct sockaddr_in serverData;
	char buffer[BUFFER_SIZE];
	int returnValue = ERROR_NO, fd;
	pid_t readingPid;

	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Opening socket");
		return ERROR_SOCKET_OPEN;
	}

	serverData.sin_family = AF_INET;
	serverData.sin_port = htons(PORT); 

	if (connect(fd, (struct sockaddr *)&serverData, sizeof(serverData)) < 0) { 
		perror("Error connecting"); 
		return ERROR_CONNECT;
	}

	readingPid = fork();
	if (readingPid == 0) {
		// Child

		printf("Child\n");
		while (1) {
		// while (CONECTADO)
			if (read(fd, buffer, BUFFER_SIZE - 1)) {
				printf("Received: \"%s\"\n", buffer); 
			}
		}
	} else if (readingPid > 0) {
		// Parent

		printf("Parent\n");
		while (1) {
		// while (CONECTADO)
			if (fgets(buffer, BUFFER_SIZE - 1, stdin)) {
				// buffer[strcspn(buffer, "\n")] = '\0';
				send(fd, buffer, strlen(buffer), 0); 
			}
		}
	} else {
		// Error
		printf("Error\n");
		returnValue = ERROR_FORK;
	}

	close(fd);
	return returnValue;
}
