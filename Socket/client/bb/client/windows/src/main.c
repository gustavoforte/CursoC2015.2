#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define IP_ADDR "192.168.150.1"
#define PORT_NO 9090

SOCKET create_socket(void);
int connect_socket(SOCKET* sock, char* ip, int port, int timeout_recv);
void disconnect_socket(SOCKET* sock);
void destroy_socket(SOCKET* sock);
int send_socket(SOCKET* sock, char* buffer, int to_send);
int recv_socket(SOCKET* sock, char* buffer, int to_read);
int keyboard_read(char* message, char* buffer, int to_read);
void show_menu(void);

int main(int argc, char *argv[])
{
    SOCKET sock = create_socket();

    if (sock != INVALID_SOCKET)
    {
        if (connect_socket(&sock, IP_ADDR, PORT_NO, 10))
        {
            char header[2] = {0x01, 0x00};
            char buffer[256] = {0};
            int n, opcao;
            //char free_mem[1000] = {0};

            //memset(free_mem, 0, 999);
            show_menu();
            /*scanf("%d", &opcao);
            switch(opcao)
            {
                case 0: header[0] = 0x00;
                        break;
                case 1: header[0] = 0x01;
                        break;
                case 2: header[0] = 0x02;
                        break;
                case 3: header[0] = 0x03;
                        break;
            }*/
            //memset((void*) header, 0, 2);
            //fgets(header, 1, stdin);

            printf("Digite a frase: ");
            //("%s", buffer);
            memset((void*) buffer, 0, 256);
            fgets(buffer, 255, stdin);

            header[1] = strlen(buffer)-1;
            //send_socket(&sock, header, 2);
            n = send_socket(&sock, buffer, strlen(buffer));

            if (n >= 0)
            {
                memset((void*) buffer, 0, 256);
                n = recv_socket(&sock, buffer, 256);

                if (n >= 0)
                {
                    printf("%s\n", buffer);
                }
                else
                {
                    printf("ERROR reading from socket");
                }
            }
            else
            {
                printf("ERROR writing to socket");
            }
        }
        else
        {
            printf("ERROR connecting");
        }

        disconnect_socket(&sock);
    }
    else
    {
        printf("ERROR opening socket");
    }

    destroy_socket(&sock);

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

int connect_socket(SOCKET* sock, char* ip, int port, int timeout_recv)
{
    int result = 0;

    if (sock && ip)
    {
        struct sockaddr_in serv_addr = {0};
        struct timeval tv = {0};

        tv.tv_sec = timeout_recv;
        setsockopt(*sock, SOL_SOCKET, SO_RCVTIMEO, (char*) &tv, sizeof(struct timeval));

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = inet_addr(IP_ADDR);
        serv_addr.sin_port = htons(PORT_NO);

        result = (connect(*sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) >= 0);
    }

    return result;
}

void disconnect_socket(SOCKET* sock)
{
    if (sock)
    {
        closesocket(*sock);
    }
}

void destroy_socket(SOCKET* sock)
{
    WSACleanup();
}

int send_socket(SOCKET* sock, char* buffer, int to_send)
{
    int sent = 0;

    if (sock && buffer && (to_send > 0))
    {
        sent = send(*sock, buffer, to_send, 0);
    }

    return sent;
}

int recv_socket(SOCKET* sock, char* buffer, int to_read)
{
    int read = 0;

    if (sock && buffer && (to_read > 0))
    {
        read = recv(*sock, buffer, to_read, 0);
    }

    return read;
}

int keyboard_read(char* message, char* buffer, int to_read)
{
    int read = 0;

    if (message && buffer && (to_read > 0))
    {
        printf(message);

        if (fgets(buffer, to_read, stdin))
        {
            read = to_read;
        }
    }

    return read;
}

void show_menu(void)
{
    printf("1. Echo\n");
    printf("2. Caixa Alta\n");
    printf("3. LEDs\n");
    printf("0. Sair\n");
    printf("Digite a funcao: ");
}
