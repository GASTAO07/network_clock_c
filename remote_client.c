#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>

int main() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Failed to create socket." << std::endl;
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("10.0.0.19"); // Replace with server's public IP address
    serverAddr.sin_port = htons(12345); // Same port as used by the server

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Connection failed." << std::endl;
        close(clientSocket);
        return 1;
    }

    while (true) {
        char buffer[1024];
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            std::cout << "Current time from server: " << buffer << std::endl;
        } else {
            std::cerr << "Failed to receive data from server." << std::endl;
            break; // If the server connection is lost, exit the loop
        }

        // You can add code here to send data to the server if needed
    }

    close(clientSocket);
    return 0;
}
