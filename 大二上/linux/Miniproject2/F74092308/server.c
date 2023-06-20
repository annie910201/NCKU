// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <limits.h>
#define PORT 8080
#define ADD 1
#define ABS 2
#define SUB 3
#define MUL 4
#define NOT 5
#define HI 6

int get_next_space(char* str, int start){
    int i;
    for(i = start; str[i] != ' ' && i < strlen(str); i++);
    return i == strlen(str) ? -1 : i;
}

long long int get_int(char* str, int start){
    long long int i;
    long long int res = 0;
    for(i = start; i < strlen(str) && str[i] >= '0' && str[i] <= '9'; i++){
        res *= 10;
        res += (str[i] - '0');
    }
    return res;
}

int main(int argc, char const *argv[])
{
	
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	char *hello = "Hello\n";
    char *del;

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
												&opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr *)&address,
								sizeof(address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
					(socklen_t*)&addrlen))<0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}

    while(1){
    	
    	memset(buffer,0,strlen(buffer));//reset the buffer
        valread=read(new_socket,buffer,1024);//get the line from client
        if(strstr(buffer,"add")!=NULL)//add condition
        	opt=ADD;
        else if(strstr(buffer,"abs")!=NULL)//find absolute value
        	opt=ABS;
        else if(strstr(buffer,"sub")!=NULL)//substract condition
        	opt=SUB;
        else if(strstr(buffer,"mul")!=NULL)//multipal condition
        	opt=MUL;
        else if(strstr(buffer,"kill")!=NULL)//end condition
        	opt=NOT;
        else if(strstr(buffer,"Hello, I'm ")!=NULL)//greet condition
        	opt=HI;
        else //other conditions
        	opt=10;
        if(opt==ADD||opt==MUL||opt==SUB){//ex: add 5 6
        	int start =get_next_space(buffer,0);//start=3
        	long long int a,b;
        	long long int ans;
        	char message[10];
        	a=get_int(buffer,start+1);//a=5
        	start=get_next_space(buffer,start+1);//start=5
        	b=get_int(buffer,start+1);//b=6
        	
        	if(start==-1||a==0||b==0)//error input
        		send(new_socket,hello,strlen(hello),0);
        	else{
        		if(opt==ADD)
        			ans=a+b;
        		else if(opt==MUL)
        			ans=a*b;
        		else
        			ans=a-b;
        		if(ans>INT_MAX||ans<INT_MIN)
        			send(new_socket,"overflowQQ\n",11,0);//return to client
        		else{
        			sprintf(message,"%lld",ans);//change number to string	
        			strcat(message,"\n");//add newline
        			send(new_socket,message,strlen(message),0);//return to client
        		}
        	}
        }
        else if(opt==ABS){
        	int start =get_next_space(buffer,0);
        	long long int a;
        	char message[10];
        	if(buffer[4]=='-')//negetive number
        		a=get_int(buffer,start+2);
        	else
        		a=get_int(buffer,start+1);
        	if(a==0||start==-1)//error input
        		send(new_socket,hello,strlen(hello),0);
        	else if(a>INT_MAX||a<INT_MIN)
        		send(new_socket,"overflowQQ\n",11,0);//return to client
        	else{
        		sprintf(message,"%lld",a);//change number to string	
        		strcat(message,"\n");//sdd newline
        		send(new_socket,message,strlen(message),0);//return to client
        	}
        }
        else if(opt==NOT){//"kill"
        	exit(EXIT_FAILURE);
        }
        else if(opt==HI){
        	int index;
        	char message[100]="Nice to meet you, ";
        	char name[100];//remember input name
        	for(int i=0;i<strlen(buffer);i++){
        		if(buffer[i]=='m'){//remember the index of "m"
        			index=i;
        			break;
        		}
        	}
        	for(int i=index+2,j=0;i<strlen(buffer);i++,j++){//i is start from name
        		name[j]=buffer[i];//also copy newline
        	}
        	strcat(message,name);
        	send(new_socket,message,strlen(message),0);//return to client
        }
        else {
        	send(new_socket,hello,strlen(hello),0);
        }
        
    }

	return 0;
}
