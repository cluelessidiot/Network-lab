#include <arpa/inet.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#define LENGTH 512 

int main(int argc,char **argv)
  {
char str1[]="This number belongs to NITC S6/S8 batch";
  char str2[]="Ok";
  char buffer[1];
  struct sockaddr_in addr1,addr2,client;
  int sockfd1,sockfd2,newsockfd1,newsockfd2;
  int len1=sizeof(addr1);
int len2=sizeof(addr2);
    if((sockfd1=socket(AF_INET,SOCK_STREAM,0)) < 0)
       { printf("socket failed");
         exit(0);
       }

    if((sockfd2=socket(AF_INET,SOCK_STREAM,0)) < 0)
       { printf("socket failed");
         exit(0);
       }
  addr1.sin_family=AF_INET;
  addr1.sin_port=htons(1234);
  addr1.sin_addr.s_addr=INADDR_ANY;

  addr2.sin_family=AF_INET;
  addr2.sin_port=htons(1238);
  addr2.sin_addr.s_addr=INADDR_ANY;

   if(bind(sockfd1,(struct sockaddr *) &addr1,len2) < 0)
       { printf("bind failed");
         exit(0);
       }
   if(bind(sockfd2,(struct sockaddr *) &addr2,len2) < 0)
       { printf("bind failed");
         exit(0);
       }
  if(listen(sockfd1,4) < 0)
     {
      printf("error in listen");
      exit(0);
     }
if(listen(sockfd2,4) < 0)
     {
      printf("error in listen");
      exit(0);
     }

   if((newsockfd1=accept(sockfd1,(struct sockaddr *) &addr1,&len1)) < 0)
      { printf("accept failed");
         exit(0);
       }
printf("client 1\n");

   if((newsockfd2=accept(sockfd2,(struct sockaddr *) &addr2,&len2)) < 0)
      { printf("accept failed");
         exit(0);
       }

char buffer1[1],buffer2[1];
   memset(buffer1,0,strlen(buffer1));
   memset(buffer2,0,strlen(buffer2));
printf("client 2\n");
     FILE *ptr1,*ptr2;char ch;
      //ptr1=fopen("RollS.txt","w");
   ptr2=fopen("RollS.txt","r");
 //
   int msg_recvd1 = 0, msg_recvd2 = 0;
while(1)     ///recv(newsockfd1, buffer1, 3, MSG_DONTWAIT)>0 || recv(newsockfd2, buffer2, 3, MSG_DONTWAIT)>0 )
//while( read(newsockfd1,buffer1,1)|| read(newsockfd2,buffer2,1))
  { ptr2=fopen("RollS.txt","r");
   // printf("cv%c",buffer1[0]);   
    
    if((msg_recvd1=recv(newsockfd1, buffer1, 1, MSG_DONTWAIT)) >0) 
    {
    //if(buffer1[0]=='1' && 0)
      //{
       printf("cl 1 presses enter\n");
   if(ch==EOF)
{             printf("c1 1");
              buffer1[0]=EOF;
                  buffer1[1]='\0';
                  send(newsockfd1,buffer1,1,0);
                  //exit(1);
                  


}
   ch=fgetc(ptr2);
   if(ch==EOF)
{
              printf("c1 2");
              buffer1[0]=EOF;
                  buffer1[1]='\0';
                  send(newsockfd1,buffer1,1,0);
                  


}

   while(ch!=10)
   {      
                    
                  buffer1[0]=ch;
                  buffer1[1]='\0';
                  send(newsockfd1,buffer1,1,0);
                  
           
       ch=fgetc(ptr2);
   }
                buffer1[0]='\n';
                  buffer1[1]='\0';
                  send(newsockfd1,buffer1,1,0);

     }
 if((msg_recvd2=recv(newsockfd2, buffer2, 1, MSG_DONTWAIT))>0 )
 {    
 //if(buffer2[0]=='2' && 0)
   //   {
       printf("cl 2 presses enter\n");
    if(ch==EOF)
{             printf("c2 1");
                buffer2[0]=EOF;
                  buffer2[1]='\0';
                  send(newsockfd2,buffer2,1,0);
                 // ptr2--;


}  

ch=fgetc(ptr2);
if(ch==EOF)
{
            printf("c2 2");
              buffer2[0]=EOF;
                  buffer2[1]='\0';
                  send(newsockfd2,buffer2,1,0);
                 // ptr2--;
			//exit(1);

}

   while(ch!=10 && ch!=EOF)
   {
                  // printf("%c",ch);
                  buffer2[0]=ch;
                  buffer2[1]='\0';
                  send(newsockfd2,buffer2,1,0);

           
       ch=fgetc(ptr2);
   }///////////////////////////////////////////////////////////////////////////////////////
                buffer2[0]='\n';
                  buffer2[1]='\0';
                  send(newsockfd2,buffer2,1,0);



/*FILE *ptr1,*ptr2;char ch;
      //ptr1=fopen("RollS.txt","w");
   ptr2=fopen("RollS.txt","r");
   ch=fgetc(ptr2);

   while(ch!='\n')
   {
       
                  buffer1[0]=ch;
                  buffer1[1]='\0';
                  write(newsockfd1,buffer1,1);

           
       ch=fgetc(ptr2);
   }
                buffer1[0]='\n';
                  buffer1[1]='\0';
                  write(newsockfd1,buffer,1);
      */
     }
     //}
      memset(buffer1,0,strlen(buffer1));
       memset(buffer2,0,strlen(buffer2));		 
  }
}
/*
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
}*/
