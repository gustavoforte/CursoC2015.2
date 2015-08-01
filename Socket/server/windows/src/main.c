#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include <errno.h>

#define PORT_NO 9090
#define MAX_SOCKETS 10

SOCKET create_socket(void);
int bind_socket(SOCKET sock, int port, int timeout_recv);
int wait_connection(SOCKET sock);
int do_processing(SOCKET sock);
void disconnect_socket(SOCKET sock);
void destroy_socket(SOCKET sock);
int send_socket(SOCKET sock, char* buffer, int to_send);
int recv_socket(SOCKET sock, char* buffer, int to_read);

int main(int argc, char *argv[])
{
    SOCKET sock = create_socket();

    if (sock != INVALID_SOCKET)
    {
        if (bind_socket(sock, PORT_NO, 10))
        {
            SOCKET sockets[MAX_SOCKETS] = {INVALID_SOCKET};
            int opened_sockets = 0;

            while (1)
            {
                int idx, max;
                if (opened_sockets < MAX_SOCKETS)
                {
                    SOCKET new_sock = wait_connection(sock);

                    if (new_sock != INVALID_SOCKET)
                    {
                        sockets[opened_sockets++] = new_sock;
                    }
                    else if (WSAGetLastError() != WSAETIMEDOUT)
                    {
                        perror("ERROR waiting");
                    }
                }

                for (idx = 0, max = opened_sockets; idx < max; idx++)
                {
                    if (sockets[idx] != INVALID_SOCKET)
                    {
                        if (!do_processing(sockets[idx]))
                        {
                            if (WSAGetLastError() != WSAETIMEDOUT)
                            {
                                printf("Disconnecting...\n");
                                disconnect_socket(sockets[idx]);
                                sockets[idx] = sockets[opened_sockets-1];
                                sockets[opened_sockets-1] = INVALID_SOCKET;
                                opened_sockets--;
                            }
                        }
                    }
                }
            }
        }
        else
        {
            perror("ERROR binding");
        }

        disconnect_socket(sock);
    }
    else
    {
        perror("ERROR opening socket");
    }

    destroy_socket(sock);

    return 0;
}

SOCKET create_socket(void)
{
    SOCKET sock = INVALID_SOCKET;
    WSADATA wsaData = {0};

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) == 0)
    {
        sock = socket(AF_INET, SOCK_STREAM, 0);
    }

    return sock;
}

int bind_socket(SOCKET sock, int port, int timeout_recv)
{
    int result = 0;

    if (sock != INVALID_SOCKET)
    {
        struct sockaddr_in serv_addr = {0};
        struct timeval tv = {0};
        
        tv.tv_usec = 100;

        setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*) &tv, sizeof(struct timeval));

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(port);

        result = bind(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == 0;
    }

    return result;
}

int wait_connection(SOCKET sock)
{
    SOCKET new_sock = INVALID_SOCKET;

    if (sock != INVALID_SOCKET)
    {
        int clilen;
        struct sockaddr_in cli_addr;

        listen(sock, MAX_SOCKETS);
        clilen = sizeof(cli_addr);

        new_sock = accept(sock, (struct sockaddr *) &cli_addr, (socklen_t*) &clilen);

        if (new_sock != INVALID_SOCKET)
        {
            struct timeval tv = {0};

            tv.tv_usec = 100;

            setsockopt(new_sock, SOL_SOCKET, SO_RCVTIMEO, (char*) &tv, sizeof(struct timeval));

            printf("New connection incoming: %s:%d\n", inet_ntoa(cli_addr.sin_addr),
                ntohs(cli_addr.sin_port));
        }
    }

    return new_sock;
}

int do_processing(SOCKET sock)
{
    int result = 0;

    if (sock != INVALID_SOCKET)
    {
        int read;
        char buffer[256] = {0};

        if ((read = recv_socket(sock, buffer, 255)) > 0)
        {
            send_socket(sock, buffer, read);
            result = 1;
        }
    }

    return result;
}

void disconnect_socket(SOCKET sock)
{
    if (sock != INVALID_SOCKET)
    {
        closesocket(sock);
    }
}

void destroy_socket(SOCKET sock)
{
    /* Empty */
}

int send_socket(SOCKET sock, char* buffer, int to_send)
{
    int sent = 0;

    if ((sock != INVALID_SOCKET) && buffer && (to_send > 0))
    {
        sent = send(sock, buffer, to_send, 0);
    }

    return sent;
}

int recv_socket(SOCKET sock, char* buffer, int to_read)
{
    int read = 0;

    if ((sock != INVALID_SOCKET) && buffer && (to_read > 0))
    {
        read = recv(sock, buffer, to_read, 0);
    }

    return read;
}
