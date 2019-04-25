#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

int
main(int argc,char* argv[])
{
	// this is holding the message
	char server_message[256] = "is this ever going to work ?";
	
	// create server socket
	int server_socket;
	server_socket = socket(AF_INET,SOCK_STREAM,0);

	// define server address
	struct sockaddr_in server_address;
	server_address.sin_port = htons(9002);
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;

	// bind the socket to our specified IP and PORT
	bind(server_socket, (struct sockaddr*) &server_address,sizeof(server_address));
	listen(server_socket, 5);

	// accepting connection
	int client_socket;
	client_socket = accept(server_socket, NULL, NULL);

	send(client_socket, server_message, sizeof(server_message),0);

	close(server_socket);
	return 0;
}