#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>

static void sig_handler(int sig) {
	printf("signal %d recieved\n", sig);
}

int main(int argc, char *argv[]) {
	signal(SIGTERM, sig_handler);
	while (true) {
		sleep(1);
	}
	return 0;
}
