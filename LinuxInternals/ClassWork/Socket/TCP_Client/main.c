#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>		

int flag = 0;

#define SERVER_IP 	"127.0.0.1"
#define	SERVER_PORT	5000
#define SERVER_LENGTH	10
#define CLIENT_BUFF	20

int main()
{
	int sock_fd;
	int c_size;

	struct sockaddr_in serv_addr;
	char client_buffer[CLIENT_BUFF];

	printf("Client requesting\n");

	//create a client TCP Socket
	if( (sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{
		printf("Error: Could not create socket");
		return 1;
	}

	//binding with client socket is optional here

	//populate it with server's adress details
	//order is imp
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERVER_PORT);
	serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

	//connect  it to a particular IP address & port
	if( (connect (sock_fd, (struct sockaddr*) &serv_addr, sizeof(serv_addr))) != 0)
	{
		printf("Error: Connecting to server failed\n");
	}
	else
	{
		printf("Connection successful\n");
	}

	//get into infinte loop as this is a server
	while(1)
	{
	
		//get the message from the client
		printf("Enter the data to be sent to the server: \n");
		fgets(client_buffer, CLIENT_BUFF, stdin);
		
		//send the data to the server
		c_size = send(sock_fd, (void *)&client_buffer, CLIENT_BUFF, 0);

		if(c_size)
		{
			printf("Message sent to server successfully, please check\n");
		}
		else
		{
			printf("Error : Message send failed\n");
		}
	
	}
	//close the sockets now
	close(sock_fd);
}
