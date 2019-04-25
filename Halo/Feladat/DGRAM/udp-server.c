#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "bingo.h"
#include <errno.h>


void error(int errnum,char* err_msg)
{
	if (errnum == -1)
	{
		printf("An error occured : \n");
		printf("%s\n",err_msg );
		printf("Error : %s (%d)\n",strerror(errno),errno );
	}
}

int Connection()
{
	int petak = 1000;
	struct sockaddr_in szerver;
	struct sockaddr_in kliens;
	int kliens_meret = sizeof(kliens);
	char on = 1;
	char szerver_cim[16];
	int flags = 0;
	int szerver_meret = sizeof szerver;
	int szelveny[9];
	int nyeroszamok[30];
	int Bingo = 0;
	int tet = 0;
	int gameOver = 0;
	int asd = 0;
	char * vege = "/ GAME OVER /\nelfogyott a penzed";
	int fd = socket(AF_INET,SOCK_DGRAM,0);
	error(fd,"Failed to create socket.");

	szerver.sin_family = AF_INET;
	szerver.sin_addr.s_addr = htonl(INADDR_ANY);
	szerver.sin_port = htons(9000);

	//printf("%s\n",buffer );
	Random_Generator(45,30,nyeroszamok);

	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof on);
   	setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (char *)&on, sizeof on);

	int binding = bind(fd,(struct sockaddr*)&szerver,sizeof(szerver));
	error(binding,"Failed to bind the socket.");

	while(gameOver != 1)
	{
		Bingo == 1 ? gameOver = 1 : gameOver == gameOver;

		// PENZ KULDESE
		   	int rec_petak = recvfrom(fd,&petak,sizeof(petak),flags,(struct sockaddr*) &kliens,&kliens_meret);
		   	error(rec_petak,"Failed to receive the message.");

			int send_petak = sendto(fd,&petak,sizeof(petak),flags,(struct sockaddr*) &kliens,kliens_meret);
		   	error(send_petak,"Failed to send the message. petak");
		// TET FOGADASA
			int rec_tet = recvfrom(fd,&tet,sizeof(tet),flags,(struct sockaddr*)&kliens,&kliens_meret);
		   	error(rec_tet,"Failed to receive the message. tet");
		   	printf("TET : %d\n",tet);
		   	printf("EGYENLEG : %d\n",petak);
		// SZELVENY FOGADASA
		   	int rec_szelveny = recvfrom(fd,szelveny,sizeof(szelveny),flags,(struct sockaddr*)&kliens,&kliens_meret);
		   	error(rec_szelveny,"Failed to receive the message.");
	   		printf("Jatekos szelvenye : \n\n");
	   		ShowSzelveny(szelveny);
	   		Sorsolas(&Bingo,nyeroszamok);
	   	// NYEROSZAMOK KULDESE
		   	int send_nyeroszam = sendto(fd,nyeroszamok,sizeof(nyeroszamok),flags,(struct sockaddr*)&kliens,kliens_meret);
		   	error(send_nyeroszam,"Failed to send the message. nyszam");
		   	CheckBingo(&Bingo,nyeroszamok,szelveny,petak,tet);
		// PENZ KULDESE
		   	int send_petak2 = sendto(fd,&petak,sizeof(petak),flags,(struct sockaddr*)&kliens,kliens_meret);
		   	error(send_petak2,"Failed to send the message.");
		// UZENET KULDESE 
	   		char * msg = "Petak : "+ petak;
	   		if (petak < 1)
		   	{
		   		int send_vege = sendto(fd,vege,sizeof(vege),flags,(struct sockaddr*)&kliens,kliens_meret);
		   		error(send_vege,"Failed to send the message.");
		   	}
		   	else
		   	{
		   		int send_msg = sendto(fd,msg,sizeof(msg),flags,(struct sockaddr*)&kliens,kliens_meret);
		   		error(send_msg,"Failed to send the message.");
		   	}

	}



	close(fd);
	return 0;

}


int main(int argc,char**argv)
{
	
	Connection();

}