#ifndef NETWORK_H
#define NETWORK_H

typedef struct {
	int sock;
} network_t;

network_t *network_open(const char *address, short port, int backlog);
int network_close(network_t *network);
network_t *network_accept(network_t *server);

#endif
