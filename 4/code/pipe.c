#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

void main() {
	int pipefd[2];
	pipe(pipefd);
	pid_t p;

	p = fork();
	if (p == 0) {
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		execlp("ls", "ls", NULL);
	}

	p = fork();
	if (p == 0) {
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		execlp("wc", "wc", "-l", NULL);
	}

	close(pipefd[0]);
	close(pipefd[1]);
	
	wait(NULL);
	wait(NULL);
}
