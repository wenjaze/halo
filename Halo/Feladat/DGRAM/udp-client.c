#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
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
	int petak = 560;
	struct sockaddr_in szerver;
	struct sockaddr_in kliens;
	char on = 1;
	char szerver_cim[16];
	int flags = 0;
	int szerver_meret = sizeof szerver;
	int kliens_meret = sizeof kliens;
	int szelveny[9];
	int nyeroszamok[30];
	int tet=0;
	int gameOver = 0;
	int Bingo = 0;
	char uzi[50];
	int kod = 1;


	// BEALLITASOK

	szerver.sin_family = AF_INET;
	szerver.sin_addr.s_addr = INADDR_ANY;
	szerver.sin_port = htons(9000);

	int fd = socket(AF_INET,SOCK_DGRAM,0);
	error(fd,"Failed to create socket.");

	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof on);
   	setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (char *)&on, sizeof on);

   	
   	while (gameOver != 1)
   	{
	   	Bingo == 1 ? gameOver = 1 : gameOver == gameOver;
		Szelveny(szelveny);
			tet = 300;
	   	// PENZ KULDESE
	   		int send_petak = sendto(fd,&petak,sizeof(petak),flags,(struct sockaddr*)&kliens,kliens_meret);
		   	error(send_petak,"Failed to send the message. petak");
		// TET KULDESE	
		   	int send_tet = sendto(fd,&tet,sizeof(tet),flags,(struct sockaddr*) &szerver,szerver_meret);
	   		error(send_tet,"Failed to send the message.");
   		// SZELVENY KULDESE
	   		int send_szelveny = sendto(fd,szelveny,sizeof(szelveny),flags,(struct sockaddr*) &szerver,szerver_meret);
	   		error(send_szelveny,"Failed to send the message.");
	   	// NYEROSZAM FOGADASA
		   	int rec_nyeroszam = recvfrom(fd,nyeroszamok,sizeof(nyeroszamok),flags,(struct sockaddr*) &szerver,&szerver_meret);
		   	error(rec_nyeroszam,"Failed to receive the message.");
		// PENZ FOGADASA
			int send_petak2 = recvfrom(fd,&petak,sizeof(petak),flags,(struct sockaddr*) &szerver,&szerver_meret);
		   	error(send_petak2,"Failed to receive the message.");
		// UZENET FOGADASA	
		   	int rec_uzi = recvfrom(fd,uzi,sizeof(uzi),flags,(struct sockaddr*) &szerver,&szerver_meret);
		   	error(rec_uzi,"Failed to receive the message.");

		   	
		
		printf("\n");
		for(int i = 0;i<MAX_NYSZ_COUNT;i++)
		{
			printf("%d#\t", i+1 );
			// if(i+1 >= 10)
			// {
			// 	printf(" ");
			// }
			printf("Nyeroszam : %d\n",nyeroszamok[i]);
		}
	   	printf("\n\n\tNyomj [Enter]-t a folytatashoz.\n");
        fflush(stdin); // option ONE to clean stdin
        getchar(); // wait for ENTER
		getchar();

   	}




	close(fd);


	return 0;
}

int main(int argc,char**argv)
{
	
	Connection();


}