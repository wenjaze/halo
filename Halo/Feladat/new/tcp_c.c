/***************************************/
/*             TCP client              */
/***************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFSIZE 1024
#define PORT_NO 2001
#define error(a,b) fprintf(stderr, a, b)

int main(int argc, char *argv[] ) {// arg count, arg vector   

   /* Declarations */
   int fd;                         // socket endpt 
   int flags;                      // rcv flags
   struct sockaddr_in server;      // socket name (addr) of server 
   struct sockaddr_in client;      // socket name of client 
   int server_size;                // length of the socket addr. server 
   int client_size;                // length of the socket addr. client 
   int bytes;                      // length of buffer 
   int rcvsize;                    // received bytes
   int trnmsize;                   // transmitted bytes
   int err;                        // error code
   int ip;                                    // ip address
   char on;                        // 
   char buffer[BUFSIZE+1];         // datagram dat buffer area
   char server_addr[16];           // server address  

   /* Initialization */
   on    = 1;
   flags = 0;
   server_size = sizeof server;
   client_size = sizeof client;
   sprintf(server_addr, "%s", argv[1]);
   ip = inet_addr(server_addr);
   server.sin_family      = AF_INET;
   server.sin_addr.s_addr = ip;
   server.sin_port        = htons(PORT_NO);
   
   /* User interface */
   printf(" Message: ");
   scanf("%s",buffer);
   bytes = strlen(buffer)+1;

   /* Creating socket */
   fd = socket(AF_INET, SOCK_STREAM, 0);
   if (fd < 0) {
      error("%s: Socket creation error.\n",argv[0]);
      exit(1);
   }

   /* Setting socket options */
   setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof on);
   setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (char *)&on, sizeof on);

   /* Connecting to the server */
   err = connect(fd, (struct sockaddr *) &server, server_size);
   if (err < 0) {
      error("%s: Cannot connect to the server.\n", argv[0]);
      exit(2);
   }

   /* Sending data to the server */
   trnmsize = send(fd, buffer, bytes, flags);
   if (trnmsize < 0) {
      error("%s: Cannot send data to server.\n", argv[0]);
      exit(3);
   }

   /* User interface */
   printf("%i bytes have been sent to server.\n", trnmsize-1);

   /* Receive data from the server */
   rcvsize = recv( fd, buffer, bytes, flags );
   if (rcvsize < 0) {
      error("%s: Cannot receive data from the socket.\n", argv[0]);
      exit(4);
   }

   /* User interface */
   if (strcmp(buffer, "Transmit is OK."))
      printf("Acknowledgement has been received from server.\n");
   else
      printf("Acknowledgement error.");

   /* Closing sockets and quit */
   close(fd);
   exit(0);
} 