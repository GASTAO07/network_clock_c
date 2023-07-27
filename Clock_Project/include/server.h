#ifndef SERVER_H
#define SERVER_H

#include <WinSock2.h> 
void handle_client(SOCKET client_socket);
void start_network_clock_server();

#endif