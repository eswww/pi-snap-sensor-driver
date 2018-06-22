#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "sensor_lib.h"

// When the user types 'x', the program will be terminated
void *hooking_keycode(void *data);

void *hooking_keycode(void *data)
{
    char key;

    while(1)
    {
        key = getchar();
        if(key == 'x')
        {
           printf("[INFO] Terminated\n");
           exit_application();
           close(*(int*)data);    // Close socket
           exit(0);
        }
    }
}

int main(void)
{
    int sock;
    char buf[BUFSIZ];
    struct sockaddr_in server;

    pthread_t hooker;

    unsigned long sensor_data = 0;

    // Init socket
    if((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("[ERROR] socket()\n");
        exit(-1);
    }

    // Init server
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(IP);
    server.sin_port = htons(PORT);

    // Connect to server
    if(connect(sock, (struct sockaddr *)&server, sizeof(server)))
    {
        perror("[ERROR] connect()\n");
        exit(-1);
    }

    if(pthread_create(&hooker, NULL, hooking_keycode, (void*)&sock) < 0)
    {
        perror("[ERROR] pthread_create()\n");
        exit(-1);
    }

    printf("[INFO] Started (if you want to terminate this program, please type 'x') \n");

    // Send to server
    while(1)
    {
        // Clear buffer and sensor data
        memset(buf, '\0', BUFSIZ);
        sensor_data = 0;

        // Get sensor data
        sensor_data = get_sensor_data();

        // Set LED and check distance
        if(set_led(sensor_data, 3000, 4000) == ENOUGH)
        {
            // It's enough distance!
            strcpy(buf, "ENOUGH");
            send(sock, buf, strlen(buf), 0);

            printf("[INFO] Send enough signal\n");
        }
        else
            printf("[INFO] It's not enough distance! - %lu\n", sensor_data);

        sleep(5);
    }

    exit_application();
    close(sock);

    return 0;
}
