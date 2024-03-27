#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netdb.h>

int send_size, recv_size ;
int main(int argc , char *argv[])
{
    int socket_desc , client_sock , recv_size;
    socklen_t c ;
    struct sockaddr_in server , client, my_addr;
    char client_message[20000];
    FILE *ptr;
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    client_sock = socket(AF_INET , SOCK_STREAM , 0);
    
    server.sin_family = AF_INET;
    server.sin_port = htons(8007);
    inet_pton (AF_INET, "127.0.0.1", &(server.sin_addr)) ; //fill in server ip address // loopback: 127.0.0.1
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("bind failed. Error");
        return 1;
    }
   printf("Socket is bound! Waiting for connections!\n");

    ptr = fopen("BM.txt", "rb");
    if (ptr == NULL) {
        perror("File open failed");
        close(socket_desc);
        return 1;
    }


    fseek(ptr, 0, SEEK_END);//seek to eof
    long fileSize = ftell(ptr);//get current value of file pointer location
    fseek(ptr, 0, SEEK_SET);//back to start of file 
    printf("File Sive pre converted: %d\n", fileSize);
   
    long fsize = htonl(fileSize) ;


 listen(socket_desc , 1); 
 client_sock = accept(socket_desc, (struct sockaddr *)&client, &c);    
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
   
    int numChucks = fileSize/ 1024; 
    int lastChunck = fileSize % 1024;


    send_size = send(client_sock, &fsize, sizeof(fsize), 0);

  char buf[1024] ;
    fseek(ptr, 0 , SEEK_SET); 
    
    for(int i =0; i< numChucks; i++)
    {
        fread(buf, 1024, 1, ptr) ;
        send(client_sock, &buf, sizeof(buf), 0);
    }

  
    fclose(ptr);
    close(client_sock);
    close(socket_desc);

    return 0;
}    
