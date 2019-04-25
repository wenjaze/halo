#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int
main()
{
	// create a socket
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);
	printf("Creating a socket...\n");

	// specify and address for the socket
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;
	printf("Specifing address for the socket...\n");
	
	printf("Checking connection issues...\n");
	int connection_status = connect(network_socket, (struct sockaddr *) &server_address,sizeof(server_address));
	// check for connection issues
	if (connection_status == -1)
	{
		printf("Something went wrong\n");
	}
	// recieve data from the server
	char server_response[256];
	recv(network_socket,&server_response,sizeof(server_response),0);
	printf("Receiving data from the server...\n");

	// print out the server's response
	printf("The server sent the data : %s\n",server_response);

	// closing socket
	close(network_socket);
	return 0;
}