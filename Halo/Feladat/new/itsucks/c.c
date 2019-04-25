#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024
#define PORT 9002

//SCSRC

int
main(int argc,char** argv)
{

	char buffer[BUFFER_SIZE] = "";
	int bytes = BUFFER_SIZE;
	struct sockaddr_in client;
	client.sin_family = AF_INET;
	client.sin_addr.s_addr = INADDR_ANY;
	client.sin_port = htons(PORT);
	
	printf("Message: ");
   	scanf("%s",buffer);

	// Creating socket
	int clientSocket = socket(AF_INET,SOCK_DGRAM,0);
	if (clientSocket == -1)
	{
		printf("Couldn't create socket.");
	}

	// Connecting to the socket
	int clientConnect = connect(clientSocket,(struct sockaddr*) & client,sizeof(client));
	if (clientConnect == -1)
	{
		printf("Couldn't connect to the server.");
	}

	

	// Recieving data from server
	int clientRecieve = recv(clientSocket,buffer,bytes,0);
	if (clientRecieve == -1)
	{
		printf("Couldn't recieve data from the server.");
	}

	// Sending data to server
	int clientSend = send(clientSocket,buffer,bytes,0);
	if (clientSend == -1)
	{
		printf("Couldn't send data to the server.");
	}

	/* User interface */
   	if (strcmp(buffer, "Transmit is OK."))
    	printf("Acknowledgement has been received from server.\n");
   	else
    	printf("Acknowledgement error.");

    printf("Server sent : %s",buffer);

    close(clientSocket);



}