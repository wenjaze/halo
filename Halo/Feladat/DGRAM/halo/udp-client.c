#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int send_packet()
{
	return 0;
}

void error(int errnum,char* err_msg)
{
	if (errnum == -1)
	{
		printf("An error occured : \n");
		printf("%s\n",err_msg );
	}
	
}



int main(int argc,char**argv)
{

	

	struct sockaddr_in szerver;
	struct sockaddr_in kliens;
	char on = 1;
	int buffer_size = 1024;
	char buffer[buffer_size+1];
	char szerver_cim[16];
	int message = 212;
	int flags = 0;
	int szerver_meret = sizeof szerver;
	int kliens_meret = sizeof kliens;

	szerver.sin_family = AF_INET;
	szerver.sin_addr.s_addr = INADDR_ANY;
	szerver.sin_port = htons(9000);

	/* User interface */
   	int bytes = strlen(buffer)+1;

	int fd = socket(AF_INET,SOCK_DGRAM,0);
	error(fd,"Failed to create socket.");

	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof on);
   	setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (char *)&on, sizeof on);

   	memset(buffer, 0,buffer_size);

   	int sent_size = sendto(fd,&message,sizeof(message),flags,(struct sockaddr*) &szerver,szerver_meret);
   	error(sent_size,"Failed to send the message.");

   	printf("Sent : %d\n", message );

   	int received_size = recvfrom(fd,&message,sizeof(message),flags,(struct sockaddr*) &szerver,&szerver_meret);
   	error(received_size,"Failed to receive the message.");

   	printf("Recieved : %d\n", message);

	close(fd);


	return 0;
}