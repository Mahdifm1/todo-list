#pragma once

#if defined(_WIN32) || defined(_WIN64)
    #include <winsock2.h>
#else
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
#endif

struct Saddr{
    int sockid;
    struct sockaddr_in address;
} typedef saddr;

saddr initialize_server() {
#if defined(_WIN32) || defined(_WIN64)
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0) {
        printf("\nError: This shity windows socket subsytsem could not be"
        " initialized. Error Code: %d. Exiting..\n", WSAGetLastError());
        exit(1);
    } else puts("Windowsd library loaded successfully :|");
#endif
    saddr s;
    s.address.sin_family = AF_INET;
    s.address.sin_port = htons(16985);
    s.address.sin_addr.s_addr = htonl(INADDR_ANY);

    s.sockid = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(bind(s.sockid, (struct sockaddr * )&s.address, sizeof(s.address)) == -1){
        perror("binding failed");
        exit(EXIT_FAILURE);
    }
    if(listen(s.sockid, 3) == -1) {
        perror("listening error");
        exit(EXIT_FAILURE);
    }
    return s;
}

int get_client(saddr s, char *buffer) {
    int address_size = sizeof(s.address);
    int client_socket;
    if((client_socket = accept(s.sockid, (struct sockaddr *)&s.address, &address_size)) == -1) {
        perror("accepting new socket failed");
        exit(EXIT_FAILURE);
    }
    recv(client_socket, buffer, 1024, 0);
    return client_socket;
}

void respond(int client_socket, char *message) {
    send(client_socket, message, strlen(message), 0);
#if defined(_WIN32) || defined(_WIN64)
    closesocket(client_socket);
#else
    close(client_socket);
#endif
}

void close_socket(saddr s) {
#if defined(_WIN32) || defined(_WIN64)
    closesocket(s.sockid);
    WSACleanup();
#else
    close(s.sockid);
#endif
}
