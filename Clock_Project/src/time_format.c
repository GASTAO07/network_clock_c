#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_SIZE 1024

void *handleRequest(void *socket_desc) {
    int sock = *(int*)socket_desc;
    char client_message[MAX_SIZE];
    memset(client_message, 0, MAX_SIZE);

    // Receive message from client
    if (recv(sock, client_message, MAX_SIZE, 0) < 0) {
        puts("recv failed");
        return NULL;
    }

    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char buffer[26];

    if (strcmp(client_message, "HH:MM:SS") == 0) {
        strftime(buffer, 26, "%H:%M:%S\n", tm_info);
    } else if (strcmp(client_message, "HH:MM") == 0) {
        strftime(buffer, 26, "%H:%M\n", tm_info);
    } else if (strcmp(client_message, "HHMMSS") == 0) {
        strftime(buffer, 26, "%H%M%S\n", tm_info);
    } else if (strcmp(client_message, "HHMM") == 0) {
        strftime(buffer, 26, "%H%M\n", tm_info);
    } else {
        strcpy(buffer, "Formato de tempo inválido! Por favor, tente novamente.\n");
    }

    write(sock, buffer, strlen(buffer));
    close(sock);
    free(socket_desc);

    return NULL;
}

int main(int argc, char *argv[]) {
    int socket_desc, client_sock, c;
    struct sockaddr_in server, client;
    
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        puts("Could not create socket");
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    if (bind(socket_desc, (struct sockaddr*)&server, sizeof(server)) < 0) {
        puts("Bind failed");
        return 1;
    }

    listen(socket_desc, 3);
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    while ((client_sock = accept(socket_desc, (struct sockaddr*)&client, (socklen_t*)&c))) {
        puts("Connection accepted");
        pthread_t sniffer_thread;
        int *new_sock = malloc(1);
        *new_sock = client_sock;

        if (pthread_create(&sniffer_thread, NULL, handleRequest, (void*)new_sock) < 0) {
            perror("Could not create thread");
            return 1;
        }

        puts("Handler assigned");
    }

    if (client_sock < 0) {
        perror("Accept failed");
        return 1;
    }

    return 0;
}
