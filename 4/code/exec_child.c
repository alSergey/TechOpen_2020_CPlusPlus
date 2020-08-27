#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void main(int argc, char *argv[]) {

	char *value = getenv("FOO");
	printf("child env FOO=%s\n", value);

	int fd = atoi(argv[1]);
	lseek(fd, 0, SEEK_SET);

	char buffer[65536];
	int r = read(fd, buffer, sizeof(buffer));
	buffer[r] = '\0';
	printf("child recieve %s\n", buffer);
	printf("child end\n");
}
