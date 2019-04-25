#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>


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
	int kliens_meret = sizeof(kliens);
	char on = 1;
	int buffer_size = 1024;
	char buffer[buffer_size+1];
	char szerver_cim[16];
	int mess = 500;
	int bytes = buffer_size;
	int flags = 0;
	int szerver_meret = sizeof szerver;
	int recv_mess = 0;

	int fd = socket(AF_INET,SOCK_DGRAM,0);
	error(fd,"Failed to create socket.");
	bzero(&szerver,szerver_meret);
	szerver.sin_family = AF_INET;
	szerver.sin_addr.s_addr = htonl(INADDR_ANY);
	szerver.sin_port = htons(9000);

	//printf("%s\n",buffer );
	

	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof on);
   	setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (char *)&on, sizeof on);

	int binding = bind(fd,(struct sockaddr*)&szerver,sizeof(szerver));
	error(binding,"Failed to bind the socket.");

   	int received_size = recvfrom(fd,&recv_mess,sizeof(recv_mess),flags,(struct sockaddr*) &kliens,&kliens_meret);
   	error(received_size,"Failed to receive the message.");

   	/* User interface */
   	printf ("Recieved : %d\n", recv_mess);

   	memset(buffer, 0,buffer_size);

   	int sent_size = sendto(fd,&mess,sizeof(mess),flags,(struct sockaddr*) &kliens,kliens_meret);
   	error(sent_size,"Failed to send the message.");

   	printf("Sent : %d\n", mess);



	close(fd);


	return 0;
}