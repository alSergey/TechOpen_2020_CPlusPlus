#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "network.h"

network_t *network_open(const char *address, short port, int backlog) {
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		return NULL;

	int enable = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) == -1) {
		close(sock);
		return NULL;
	}

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	if (inet_aton(address, &addr.sin_addr) == 0) {
		close(sock);
		return NULL;
	}
	addr.sin_port = htons(port);

	if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
		close(sock);
		return NULL;
	}

	if (listen(sock, backlog) == -1) {
		close(sock);
		return NULL;
	}

	network_t *network = calloc(1, sizeof(network_t));
	if (!network) {
		close(sock);
		return NULL;
	}
	
	network->sock = sock;

	return network;
}

int network_close(network_t *network) {

	int rc = close(network->sock);
	free(network);
	return rc;
}

network_t *network_accept(network_t *server) {
	int accepted_sock = accept(server->sock, NULL, NULL);
	if (accepted_sock == -1)
		return NULL;

	network_t *client = calloc(1, sizeof(network_t));
	if (!client) {
		close(accepted_sock);
		return NULL;
	}
	
	client->sock = accepted_sock;

	return client;
}
