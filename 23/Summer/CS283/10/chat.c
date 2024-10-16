/*****************************************

@file		chat.c

@author	Jacob Andrew

@date		9/3/2023

@purpose	To create a client that chats with a server on tux3

*****************************************/

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

#define INPUT_SIZE 2048 

void* reciever(void* j);
void* sender(void* a);
int sock;

/*
@brief	receives lines from the server
@param	none
@return	void
*/
void* reciever(void* dummy)
{
   int result;
   char line[INPUT_SIZE];
   
   pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &result);

   while(1)
   {
      result = recv(sock, line, INPUT_SIZE - 1, 0);
      line[result] = '\0';
      
      write(1, line, result);
   }

   pthread_exit(NULL);
}

/*
@brief	sends a line to the server
@param	buffer name
@return	void
*/
void* sender(void* name)
{
   int result; 
   char line[INPUT_SIZE];

   send(sock, name, strlen(name), 0);

   while(1){
      
      result = read(0, line, INPUT_SIZE - 1);
		
		//Stop sending if null line or new line
      if( result <= 0 || line[0] == '\n' )
      {
         break;
      }

      send(sock, line, result, 0);
   }

   pthread_exit(NULL);
}

/*
@brief	main function - sets up connection and threads
@param	input args
@return 	0 if successful
			2 if connection error
			3 if thread 1 error
			4 if thread 2 error
*/
int main(int argc, char* argv[]){

   struct sockaddr_in server;
   pthread_t t1;
   pthread_t t2;

	//tux3 IPv4 address
   char tuxAddr[]= "10.246.251.13";

	//Establishing socaetk
   sock = socket(AF_INET, SOCK_STREAM, 0);
   server.sin_family = AF_INET;
   server.sin_port = htons(2023);
   inet_aton(tuxAddr, &server.sin_addr);

   if( connect(sock, (struct sockaddr*) &server, sizeof(struct sockaddr_in)) < 0)
   {
      perror("Connection error");
      exit(2);
   }

   if( pthread_create(&t1, NULL, reciever, NULL) != 0)
   {
      perror("Thread 1 creation error");
      exit(3);
   }

   if( pthread_create( &t2, NULL, sender, argv[1]) != 0)
   {
      perror("Thread 2 creation error");
      exit(4);
   }

   pthread_join(t2, NULL);
   pthread_cancel(t1);
   shutdown(sock, SHUT_RDWR);
   
   exit(0);
}

      
   
   
