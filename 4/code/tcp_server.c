#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

	int server_sock = socket(AF_INET, SOCK_STREAM, 0);

	int enable = 1;
	setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)); 

	struct sockaddr_in server_addr; 
	memset(&server_addr , 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(1234);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)); 

	listen(server_sock, 5);

	struct sockaddr_in client_addr;
	socklen_t client_addr_len;
	int client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_addr_len);

	char client_ip[16];
	inet_ntop(client_addr.sin_family, &client_addr.sin_addr, client_ip, sizeof(client_ip));
	printf("recieved connection from %s:%d\n", client_ip, client_addr.sin_port);

	char buffer[65536];
	int r = read(client_sock, buffer, sizeof(buffer));
	buffer[r] = '\0';
	printf("read %d bytes %s\n", r, buffer);

	write(client_sock, "response\n", 9);

	close(client_sock);
	close(server_sock);
	return 0;
}
