#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFSIZE 2048

void *recieverHandler(void *j);
void *senderHandler(void *a);

int sock;

int 
main(int argc, char *argv[])
{
	pthread_t tid1;
	pthread_t tid2;
	struct sockaddr_in server;
   int con;
	char tuxIpAddr[] = "10.246.251.13";
	
	sock = socket(AF_INET, SOCK_STREAM,0);
	server.sin_family = AF_INET;
	server.sin_port = htons(2002);
	inet_aton(tuxIpAddr, &server.sin_addr);

   con = connect(sock, (struct sockaddr *) &server, sizeof(struct sockaddr_in));
   printf("%d\n", con);

	if(con < 0)
	{
		perror("ERROR CONNECT");
		exit(2);
	}

	if(pthread_create(&tid1, NULL, recieverHandler, NULL) != 0)
	{
		perror("ERROR PTHREAD 1 CREATE");
		exit(3);
	}
	if(pthread_create(&tid2, NULL, senderHandler, argv[1]) != 0)
	{
		perror("ERROR PTHREAD 2 CREATE");
		exit(4);
	}
	pthread_join(tid2, NULL);
	pthread_cancel(tid1);

	shutdown(sock, SHUT_RDWR);

	exit(0);
}

void
*recieverHandler(void *dummy)
{
   printf("Reciever\n");
	int x;
	char buf[BUFSIZE];
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &x);

	while(1)
	{
		x = recv(sock,buf,BUFSIZE - 1,0);
		buf[x] = '\0';
		write(1,buf,x);
	}
	pthread_exit(NULL);

}

void
*senderHandler(void *name)
{
   printf("Sender\n");
	int x;
	char buf[BUFSIZE];
   printf("Sending...");
	send(sock,name, strlen(name), 0);

	while(1)
	{
		x = read(0,buf,BUFSIZE - 1);
		if ( x <= 0 || buf[0] == '\n')
		{
			break;
		}
		buf[x] = '\0';

		send(sock, buf, x , 0);
	}
	pthread_exit(NULL);
}
