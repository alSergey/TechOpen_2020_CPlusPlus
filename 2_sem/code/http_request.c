#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "http_request.h"

#define BUFFER_SIZE 4096

http_request_t *http_request_create() {
	http_request_t *request = calloc(1, sizeof(http_request_t));
	return request;
}

void http_request_destroy(http_request_t *request) {
	free(request->method);
	free(request->url);
	free(request->protocol);
	free(request->host);
	free(request);
}

static int readline(int fd, char *buffer, size_t buffer_size) {

	size_t i = 0;
	while (i < buffer_size - 1) {
		char c;
		int r = read(fd, &c, sizeof(c));
		if (r <= 0)
			return -1;
		if (c == '\n')
			break;
		buffer[i++] = c;
	}

	if (buffer[i - 1] == '\r')
		i--;

	buffer[i] = '\0';

	return i;
}

int http_request_parse(int fd, http_request_t *request) {
	int buffer_len;
	char buffer[BUFFER_SIZE];

	buffer_len = readline(fd, buffer, sizeof(buffer));
	if (buffer_len == -1)
		return -1;

	char *method_begin = buffer;
	char *method_end = strchr(method_begin, ' ');
	if (method_end == NULL)
		return -1;

	request->method = strndup(method_begin, method_end - method_begin);

	char *url_begin = method_end + 1;
	while (*url_begin == ' ')
		url_begin++;
	char *url_end = strchr(url_begin,  ' ');
	if (url_end == NULL)
		return -1;

	request->url = strndup(url_begin, url_end - url_begin);

	char *protocol_begin = url_end + 1;
	while (*protocol_begin == ' ')
		protocol_begin++;
	char *protocol_end = buffer + buffer_len;

	request->protocol = strndup(protocol_begin, protocol_end - protocol_begin);

	while (1) {
		buffer_len = readline(fd, buffer, sizeof(buffer));
		if (buffer_len == -1)
			return -1;
		if (buffer_len == 0)
			break;

		char *header_name_begin = buffer;
		char *header_name_end = strchr(header_name_begin, ':');	
		if (header_name_end == NULL)
			continue;
		char *header_value_begin = header_name_end + 1;
		while (*header_value_begin == ' ')
			header_value_begin++;
		char *header_value_end = buffer + buffer_len;

		if (strncmp(header_name_begin, "Host", header_name_end - header_name_begin) == 0)
			request->host = strndup(header_value_begin, header_value_end - header_value_begin);
	}

	return 0;
}
