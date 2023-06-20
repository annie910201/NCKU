// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080

int main(int argc, char const *argv[])
{
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	//char *hello = "Hello from client";
	char buffer[1024] = {0};

    usleep(500000);

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}
	char str[100];
	while(1){
		memset(str,0,strlen(str));//reset str
	    	memset(buffer,0,strlen(buffer));//reset buffer
		scanf("%[^\n]",str);
		getchar();//take the newline in buffer away
		strcat(str,"\n");
		send(sock,str,strlen(str),0);//send to server
		if(!strcmp(str,"kill\n"))
			break;
		valread=read(sock,buffer,1024);//get from server
		printf("%s",buffer);//print to file
		sleep(0.05);//delay time
	}
	return 0;
}
