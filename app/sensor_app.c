#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 2324
#define IP "127.0.0.1"

int main(void)
{
    int count = 0;    // for testing
    int sock;
    char buf[BUFSIZ];
    struct sockaddr_in server;

    // Init socket
    if((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("[ERROR] socket()\n");
        exit(0);
    }

    // Init server
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(IP);
    server.sin_port = htons(PORT);

    // Connect to server
    if(connect(sock, (struct sockaddr *)&server, sizeof(server)))
    {
        perror("[ERROR] connect\n");
        exit(0);
    }

    memset(buf, '\0', BUFSIZ);
    strcpy(buf, "temp");
    send(sock, buf, strlen(buf), 0);

    close(sock);
    return 0;
}
