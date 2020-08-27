#include <stdio.h>
#include <unistd.h>

#include "hserver.h"
#include "http.h"
#include "log.h"
#include "process.h"
#include "network.h"

int hserver_run(hserver_config_t *config) {

	log_t *log = log_open(config->log_file_name);
	if (!log) {
		fprintf(stderr, "can't open log file\n");
		return -1;
	}

	log_info(log, "\n");
	log_info(log, "hserver started");

	if (process_daemonize() == -1) {
		log_error(log, "can't daemonize process");
		return -1;
	}

	if (process_setup_signals() == -1) {
		log_error(log, "can't setup signals");
		return -1;
	}

	network_t *server = network_open(config->address, config->port, config->backlog); 
	if (!server) {
		log_error(log, "can't open network");
		return -1;
	}

	while (1) {
		network_t *client = network_accept(server);

		if (process_is_exited)
			break;

		if (client) {
			log_info(log, "accepted new connection");
			http_handle(config->root, client->sock);
			network_close(client);
		}
		else
			continue;
	}

	network_close(server);

	log_info(log, "hserver stopped");

	log_close(log);

	return 0;
}

int main(int argc, char *argv[]) {
	hserver_config_t config = {
		.log_file_name = "/var/log/hserver/error.log",
		.address = "127.0.0.1",
		.port = 80,
		.backlog = 128,
		.root = "/var/www/",
	};

	return hserver_run(&config);
}
