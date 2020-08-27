#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

int http_response_send_status(int fd, const char *protocol, int status, const char *message);
int http_response_send_nl(int fd);
int http_response_send_header(int fd, const char *name, const char *value);
int http_response_send_header_int(int fd, const char *name, int value);
int http_response_send_file(int client_fd, int file_fd); 

#endif
