#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

	int client_sock = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in server_addr; 
	memset(&server_addr , 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(1234);
	inet_aton("127.0.0.1", &server_addr.sin_addr);

	sendto(client_sock, "request\n", 8, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));

	char buffer[65536];
	int r = read(client_sock, buffer, sizeof(buffer));
	buffer[r] = '\0';
	printf("read %d bytes %s\n", r, buffer);

	close(client_sock);
	return 0;
}
