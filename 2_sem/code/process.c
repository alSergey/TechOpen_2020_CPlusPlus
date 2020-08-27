#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "process.h"

int process_is_exited = 0;

static void process_sigterm_handler(int sig) {
	process_is_exited = 1;
}

int process_daemonize() {
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	pid_t pid = fork();
	if (pid == -1)
		return -1;

	if (pid != 0)
		exit(0);

	setsid();

	return 0;
}

int process_setup_signals() {
	if (signal(SIGTERM, process_sigterm_handler) == SIG_ERR)
		return -1;
	return 0;
}
