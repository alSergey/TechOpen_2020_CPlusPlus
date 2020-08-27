#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include "http_response.h"

#define BUFFER_SIZE 4096

int http_response_send_status(int fd, const char *protocol, int status, const char *message) {
	char buffer[BUFFER_SIZE];
	int buffer_len = snprintf(buffer, sizeof(buffer), "%s %d %s\n", protocol, status, message);
	return write(fd, buffer, buffer_len);
}

int http_response_send_nl(int fd) {
	return write(fd, "\n", 1);
}

int http_response_send_header(int fd, const char *name, const char *value) {
	char buffer[BUFFER_SIZE];
	int buffer_len = snprintf(buffer, sizeof(buffer), "%s: %s\n", name, value);
	return write(fd, buffer, buffer_len);
}

int http_response_send_header_int(int fd, const char *name, int value) {
	char buffer[BUFFER_SIZE];
	int buffer_len = snprintf(buffer, sizeof(buffer), "%s: %d\n", name, value);
	return write(fd, buffer, buffer_len);
}

int http_response_send_file(int client_fd, int file_fd) {

	char buffer[BUFFER_SIZE];
	while (1) {
		int rc = read(file_fd, buffer, sizeof(buffer));
		if (rc == -1)
			return -1;
		else if (rc == 0)
			break;

		if (write(client_fd, buffer, rc) != rc)
			return -1;
	}

	return 0;
}
