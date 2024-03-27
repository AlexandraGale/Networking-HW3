#include <stdio.h>
#include <stdlib.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<netdb.h>

struct sockaddr_in sa ;
int main()
        { int err;
          char my_buf[1024] ;
          char *msg = "I am your main socket squeeze" ;
          FILE *ptr ; 
          long fileSize;
          ssize_t recv_size;

         int my_sock = socket(AF_INET, SOCK_STREAM, 0) ;
         sa.sin_family   = AF_INET ;
         sa.sin_port     = htons(8007) ;
         inet_pton(AF_INET, "127.0.0.1" , &(sa.sin_addr)) ; //fill in IP address of server //
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

      // Receive the number of chunks sent by the server
      int numChunks;
      recv_size = recv(my_sock, &numChunks, sizeof(numChunks), 0);
      if (recv_size <= 0) {
          // Handle error or connection closed by the server
      } else {
          printf("Received number of chunks: %d\n", numChunks);
      }

      // Receive the value of the last chunk sent by the server
      int lastChunk;
      recv_size = recv(my_sock, &lastChunk, sizeof(lastChunk), 0);
      if (recv_size <= 0) {
          // Handle error or connection closed by the server
      } else {
          printf("Received last chunk value: %d\n", lastChunk);
      }
            
/*char buf[1024];

      FILE *ptrFile = fopen( ptr, "wb");

        for(int i = 0; i < 0; i++)

        {
        fwrite(buf, 1024, 1, ptr) ;
        }
    
        
         /*printf ("Sending Message to Server!\n") ;
         send (my_sock, msg, 32,  0) ;
         printf ("Receiving Message from Server!\n") ;
         int recv_size = recv(my_sock , my_buf , 32 , 0) ;
         printf("Here is the message from server: \n%s\n", my_buf) ;
         }*/

      fclose(ptr);
      close(my_sock);

      return 0; 
      }