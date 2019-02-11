#include <arpa/inet.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

void server();
void client();


int main(int argc,char **argv)
  {  
   char buffer[1];
  struct sockaddr_in addr;
  int sockfd,newsockfd;
  int len=sizeof(addr);
    if((sockfd=socket(AF_INET,SOCK_STREAM,0)) < 0)
        { printf("socket failed");
         exit(0);
       }

  addr.sin_family=AF_INET;
  addr.sin_port=htons(1234);

  inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);

    if(connect(sockfd,(struct sockaddr *) &addr,len) < 0)
     { printf("connection failed");
         exit(0);
       }

   /*     buffer[0]='a';
        buffer[1]='\0';
         char *hello="hey...";
        send(sockfd , hello , strlen(hello) , 0 );
      write(sockfd,buffer,1);*/
    FILE *ptr1,*ptr2;
ptr1=fopen("RollC1.txt","w");        
while(1)
{
   char ch;
    ch=fgetc(stdin);
     // ptr1=fopen("RollC1.txt","a");   
   if(ch==10)
    {
       char *hello="1";
        printf("client 1 press enter and sends...\n");
        send(sockfd , hello , strlen(hello) , 0 );
         
           recv(sockfd,buffer,1,0);
              if(buffer[0]==EOF)
           {  printf("ec1");
             exit(1);
           }
                  
         while(buffer[0]!=10) 
          {                       fprintf(ptr1,"%c",buffer[0]);
          			  //fputs(buffer,ptr1);
			  
         // printf("%c",buffer[0]);
	   memset(buffer,0,1);
           recv(sockfd,buffer,1,0);
}
fputs("\n",ptr1);                 
    }


}

}
/*  struct hostent *server;
    server=gethostbyname("127.0.0.1");

   bcopy((char *) server->h_addr,(char *) &addr.sin_addr.s_addr,server->h_length);

   connect(sockfd,(struct sockaddr *) &addr,len);
*/

/*    char ch;
    FILE *ptr1,*ptr2;
     ptr1=fopen("RollC.txt","r");
     ch=fgetc(ptr1);
  buffer[0]=ch;
        buffer[1]='\0';


    while(ch!=EOF)
        {


        write(sockfd,buffer,1);
        ch=fgetc(ptr1);
        buffer[0]=ch;
        buffer[1]='\0';
        }
        buffer[0]=EOF;
        buffer[1]='\0';
        write(sockfd,buffer,1);


     ptr2=fopen("NumberC.txt","w");
     memset(buffer,0,1);
     buffer[1]='\0';
     read(sockfd,buffer,1);
      buffer[1]='\0';
     while(buffer[0] != '\n')
       {

        fprintf(ptr2,"%s",buffer);
      memset(buffer,0,1);
         read(sockfd,buffer,1);
         buffer[1]='\0';
        }




}*/
