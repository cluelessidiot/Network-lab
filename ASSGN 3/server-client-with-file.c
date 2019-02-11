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
  if(!strcmp(argv[1],"server"))
      server();
  else if(!strcmp(argv[1],"client"))
      client();
   }

void server()
 {
   char str1[]="This number belongs to NITC S6/S8 batch";
  char str2[]="Ok";
  char buffer[1];
  struct sockaddr_in addr,client;
  int sockfd,newsockfd;
  int len=sizeof(addr);
    if((sockfd=socket(AF_INET,SOCK_STREAM,0)) < 0)
       { printf("socket failed");
         exit(0);
       }


  addr.sin_family=AF_INET;
  addr.sin_port=htons(1234);
  addr.sin_addr.s_addr=INADDR_ANY;


   if(bind(sockfd,(struct sockaddr *) &addr,len) < 0)
       { printf("bind failed");
         exit(0);
       }

  if(listen(sockfd,4) < 0)
     {
      printf("error in listen");
      exit(0);
     }


   if((newsockfd=accept(sockfd,(struct sockaddr *) &client,&len)) < 0)
      { printf("accept failed");
         exit(0);
       }
int a;
  FILE *ptr1,*ptr2;
  ptr1=fopen("RollS.txt","w");
  memset(buffer,0,strlen(buffer));
     buffer[1]='\0';
     read(newsockfd,buffer,1);
      buffer[1]='\0';
    while(buffer[0] != EOF)
       {

        fprintf(ptr1,"%s",buffer);
      memset(buffer,0,strlen(buffer));
         read(newsockfd,buffer,1);
         buffer[1]='\0';
        }

    char ch;
    memset(buffer,0,strlen(buffer));
   fclose(ptr1);
   ptr2=fopen("RollS.txt","r");
   ch=fgetc(ptr2);

   while(ch!='\n')
   {
       if(ch>='0' && ch<='9')
           {   buffer[0]=ch;
                  buffer[1]='\0';
                  write(newsockfd,buffer,1);

           }
       ch=fgetc(ptr2);
   }
        buffer[0]='\n';
                  buffer[1]='\0';
                  write(newsockfd,buffer,1);

}

void client()
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


/*  struct hostent *server;
    server=gethostbyname("127.0.0.1");

   bcopy((char *) server->h_addr,(char *) &addr.sin_addr.s_addr,server->h_length);

   connect(sockfd,(struct sockaddr *) &addr,len);
*/

    char ch;
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




}
