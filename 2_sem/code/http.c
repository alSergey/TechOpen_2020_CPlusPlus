#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "http.h"
#include "http_request.h"
#include "http_response.h"

int http_handle(const char *root, int client_fd) {
	http_request_t *request = http_request_create();
	if (!request)
		return -1;

	if (http_request_parse(client_fd, request) == -1) {
		http_request_destroy(request);
		return -1;
	}

	if (strcmp(request->method, "GET") != 0) {
		http_request_destroy(request);
		return -1;
	}

	int version_major, version_minor;
	if (sscanf(request->protocol, "HTTP/%d.%d", &version_major, &version_minor) != 2 ||
		version_major != 1 || (version_minor != 0 && version_minor != 1)) {
		http_request_destroy(request);
		return -1;
	}

	char *host = request->host;
	if (!host)
		host = "localhost";
	size_t host_len = strlen(host);

	char *url = request->url;
	size_t url_len = strlen(url);

	if (url_len == 1 && *url == '/') {
		url = "/index.html";
		url_len = strlen(url);
	}

	size_t file_name_len = strlen(root) + host_len + url_len;
	char *file_name = malloc(file_name_len);
	if (!file_name) {
		http_request_destroy(request);
		return -1;
	}

	sprintf(file_name, "%s%s%s", root, host, url);

	int file_fd = open(file_name, O_RDONLY);
	if (file_fd == -1) {
		http_response_send_status(client_fd, request->protocol, 404, "Not found");
		http_response_send_header(client_fd, "Connection", "close");
		http_response_send_nl(client_fd);
		http_request_destroy(request);
		return -1;
	}

	struct stat file_stat;
	if (fstat(file_fd, &file_stat) == -1) {
		http_response_send_status(client_fd, request->protocol, 404, "Not found");
		http_response_send_header(client_fd, "Connection", "close");
		http_response_send_nl(client_fd);
		http_request_destroy(request);
		return -1;
	}

	char *content_type = NULL;
	char *ext = strchr(file_name, '.');
	if (ext) {
		ext++;
		if (strcmp(ext, "html") == 0)
			content_type = "text/html";
		else if (strcmp(ext, "jpg") == 0)
			content_type = "image/jpg";
		else if (strcmp(ext, "gif") == 0)
			content_type = "image/gif";

	}

	http_response_send_status(client_fd, request->protocol, 200, "OK");
	if (content_type)
		http_response_send_header(client_fd, "Content-Type", content_type);
	http_response_send_header(client_fd, "Connection", "close");
	http_response_send_header_int(client_fd, "Content-Length", file_stat.st_size);
	http_response_send_nl(client_fd);
	http_response_send_file(client_fd, file_fd);

	close(file_fd);
	http_request_destroy(request);

	return 0;
}
