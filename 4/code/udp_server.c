#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int server_sock = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in server_addr; 
	memset(&server_addr , 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(1234);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)); 

	char buffer[65536];
	struct sockaddr_in client_addr;
	memset(&client_addr, 0, sizeof(client_addr));
	socklen_t client_addr_len = sizeof(client_addr);;
	int r = recvfrom(server_sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_addr, &client_addr_len);

	buffer[r] = '\0';
	printf("read %d bytes %s\n", r, buffer);

	sendto(server_sock, "response\n", 9, 0, (struct sockaddr*)&client_addr, client_addr_len);

	close(server_sock);
	return 0;
}
