#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

typedef struct {
	char *method;
	char *url;
	char *protocol;
	char *host;
} http_request_t;

http_request_t *http_request_create();
void http_request_destroy(http_request_t *request);
int http_request_parse(int fd, http_request_t *request);

#endif
