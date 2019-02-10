
// Client side c
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080 
   
int main(int argc,char **argv) 
{ 
//client program................................	
if(strcmp(argv[1],"client")==0)
{
    struct sockaddr_in address; 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char *hello = "Hello from client"; 
    char* check="This number belongs to NITC S6/S8 batch";
    char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    memset(&serv_addr, '0', sizeof(serv_addr)); 
   
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
    //code of client chating............
    while(1)
    {
      char roll[100];
      scanf("%[^\n]%*c", roll);
       send(sock , roll , strlen(roll) , 0 ); 
       valread = read( sock , buffer, 1024); 
       printf("%s\n",buffer );
     //  printf("dffs");
       if(strcmp(buffer,check)==0)
      break;
         
    }
   // send(sock , hello , strlen(hello) , 0 );  
    //valread = read( sock , buffer, 1024); 
    //printf("%s\n",buffer ); 
    return 0; 
}
//server program........................................
if(strcmp(argv[1],"server")==0)
{
 int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char *hello = "OK.."; 
    char *confirm_message="This number belongs to NITC S6/S8 batch";
       
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
  
    while(1)
    { 
    valread = read( new_socket , buffer, 1024); 
    if(strcmp(buffer,"Hello:B160345CS")==0)
      break;
    send(new_socket , hello , strlen(hello) , 0 );
    }          
  
    send(new_socket , confirm_message , strlen(confirm_message) , 0 ); 
  
    return 0; 
}
} 

