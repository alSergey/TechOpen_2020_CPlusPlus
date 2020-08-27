#ifndef HSERVER_H
#define HSREVER_H

typedef struct {
	const char *log_file_name;
	const char *address;
	short port;
	int backlog;
	const char *root;
} hserver_config_t;

#endif
