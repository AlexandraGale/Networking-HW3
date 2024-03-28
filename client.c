#include <stdio.h>
#include <stdlib.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<netdb.h>

struct sockaddr_in sa ;
#define ClientIP "127.0.0.1"
int main()
        { int err;
          char my_buf[1024] ;
          char *msg = "I am your main socket squeeze"; 
         
          ssize_t recv_size;

         int my_sock = socket(AF_INET, SOCK_STREAM, 0) ;
         sa.sin_family   = AF_INET ;
         sa.sin_port     = htons(8007) ;
         inet_pton(AF_INET, ClientIP, &(sa.sin_addr)) ; //fill in IP address of server //
         printf("BEFORE CONNECT\n") ;
         int x = connect(my_sock, (struct sockaddr *) &sa, sizeof(sa)) ;
         if(x < 0)
		     perror("Connect") ;
        
       

      // Receive the file size sent by the server
        long fsize;
        recv_size = recv(my_sock, &fsize, sizeof(fsize), 0);
      if (recv_size <= 0) {
          // Handle error or connection closed by the server
      } else {
          printf("Received file size: %ld\n", fsize);
      }
      long fileSize = htonl(fsize); 
      int numChuncks = fileSize/ 1024; 
      int lastChunck = fileSize % 1024;
  

      FILE *ptr = fopen("bmOUT.txt", "wb"); 
      char buf[1024] ;
      for(int i = 0; i < numChuncks ; i++)
      {
        recv(my_sock, buf, sizeof(buf), 0);
        fwrite(buf, 1024, 1, ptr) ;//how does this work todo, frite moves the ptr as part of its functionality
      }
    
      if (lastChunck > 0) 
      {
        recv(my_sock, buf, sizeof(buf), 0);
        fwrite(buf, lastChunck, 1, ptr) ;
      }
     

      fclose(ptr);
      close(my_sock);

      return 0; 
      }