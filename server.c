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

    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    client_sock = socket(AF_INET , SOCK_STREAM , 0);
    
    server.sin_family = AF_INET;
    server.sin_port = htons(8003);
    inet_pton (AF_INET, "xxx.xx.xxx.x", &(server.sin_addr)) ; //fill in server ip address
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("bind failed. Error");
        return 1;
    }
   printf("Socket is bound! Waiting for connections!\n") ;

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
