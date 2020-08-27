#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

void main() {

	int fd = open("data", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

	char arg[16];
	sprintf(arg, "%d", fd);

	pid_t pid = fork();
	if (pid != 0) {
		printf("master send ping\n");
		write(fd, "ping", 4);
		wait(NULL);
		printf("master end\n");
	}
	else {
		char *argv[] = {"exec_child", arg, NULL};
		char *envp[] = {"FOO=BAR", NULL};
		execve("exec_child", argv, envp);
	}
}
