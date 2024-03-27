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

    ptr =fopen("BM(1).txt", "W");
    fseek(ptr, 0, SEEK_END);//seek to eof
    long fileSize = ftell(ptr);//get current value of file pointer location
    fseek(ptr, 0, SEEK_SET);//back to start of file 

    long fsize = htonl(fileSize) ;
    send_size = send(client_sock, &fsize, sizeof(fsize),0);
    

 listen(socket_desc , 1); 
 client_sock = accept(socket_desc, (struct sockaddr *)&client, &c);    
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }

    recv_size = recv(client_sock, client_message , 32 , 0) ;

    printf("Got this from Client %s\n", client_message) ;
   
    sprintf(client_message,"YOA DOG!\n") ; 
   
    send_size = send(client_sock , client_message , 32, 0);
    
    return 0;
}
