#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void main() {

	char *path = getenv("PATH");
	printf("PATH=%s\n", path);

	char *foo = getenv("FOO");
	printf("FOO=%s\n", foo);

	setenv("BAR", "1", 1);

	pid_t pid = fork();
	if (pid != 0)
		return;
	else {
		char *bar = getenv("BAR");
		printf("BAR=%s\n", bar);
		return;
	}
}
