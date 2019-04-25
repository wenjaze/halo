#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>

//SBLARSC
#define BUFFER_SIZE 1024
#define PORT 9002

int
main(int argc,char** argv)
{

	char buffer[BUFFER_SIZE] = "Good Morning ladies n' gentlemen."; // server message
	struct sockaddr_in server; // server sturct
	int bytes = BUFFER_SIZE;
	server.sin_family = AF_INET; // using TCP/IP protocol
	server.sin_port = htons(PORT); // using predefined PORT
	server.sin_addr.s_addr = INADDR_ANY; // giving the server local host ip

	
	// Creating server socket
	int serverSocket = socket(AF_INET,SOCK_STREAM,0); 
	if (serverSocket == -1)
	{
		printf("Couldn't create server socket.");
	} 
	
	// Binding
	int serverBind = bind(serverSocket,(struct sockaddr*) &server,sizeof(server));
	if (serverBind == -1)
	{
		printf("Couldn't bind to server.\n");
	}

	// Listening
	int serverListen = listen(serverSocket,5);
	if (serverListen == -1)
	{
		printf("Couldn't listen to the client.");
	}

	// Accepting
	int clientSocket = accept(serverSocket,NULL,NULL);
	if (clientSocket == -1)
	{
		printf("Couldn't accept client.");
	}

	// Recieving
	int serverRecieved = recv(clientSocket,buffer,bytes,0);
	if (serverRecieved == -1)
	{
		printf("Couldn't receive any data.");
	}

	// Printing out message
	printf("Message : %s (%d bytes)",buffer,bytes);

	// Sending
	sprintf(buffer,"Transmit is OK.");
   	bytes = strlen(buffer) + 1;
	int serverSend = send(clientSocket,buffer,bytes,0);
	if (serverSend == -1)
	{
		printf("Couldn't send data to client.");
	}

	/* User interface */
   	printf ("Acknowledgement has been sent to the client.\n");
	

	// Closing
	close(serverSocket);

}