#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

void fatal_error() {
    write(2, "Fatal error\n", 12);
    exit(1);
}

char str_buf[42*4096], read_buf[42*4096], write_buf[42*4096+42];
int array_fd[65536], max_fd = 0, next_fd = 0;
fd_set active, ready_read, ready_write;

void send_all(int except_sock) {
    int len = strlen(write_buf);
    for (int sock = 0; sock <= max_fd; ++sock) {
        if (FD_ISSET(sock, &ready_write) && sock != except_sock)
            send(sock, write_buf, len, 0);
    }
    return ;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        write(2, "Wrong number of arguments\n", 26);
        exit(1);
    }
    int port = atoi(argv[1]);
    FD_ZERO(&active);
    bzero(array_fd, sizeof(array_fd));

    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0)
        fatal_error();
    max_fd = server;
    FD_SET(server, &active);

    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    bzero(&addr, addr_len);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = (1 << 24) | 127;
    addr.sin_port = (port >> 8) | (port << 8);

    if (bind(server, &addr, addr_len) < 0)
        fatal_error();
    if (listen(server, SOMAXCONN) < 0)
        fatal_error();

    while (1) {
        ready_read = ready_write = active;
        if (select(max_fd + 1, &ready_read, &ready_write, 0, 0) < 0)
            continue;
        for (int sock = 0; sock <= max_fd; ++sock) {
            if (FD_ISSET(sock, &ready_read) && sock == server) {
                int client = accept(server, &addr, &addr_len);
                if (client < 0)
                    continue ;
                if (client > max_fd)
                    max_fd = client;
                array_fd[client] = next_fd++;
                FD_SET(client, &active);
                sprintf(write_buf, "server: client %d just arrived\n", array_fd[client]);
                send_all(client);
                break ;
            }
            if (FD_ISSET(sock, &ready_read) && sock != server) {
                int read_count = recv(sock, read_buf, 42*4096, 0);
                if (read_count <= 0) {
                    sprintf(write_buf, "server: client %d just left\n", array_fd[sock]);
                    send_all(sock);
                    FD_CLR(sock, &active);
                    close(sock);
                    break ;
                }
                else {
                    for (int i = 0, j = 0; i < read_count; ++i, ++j) {
                        str_buf[j] = read_buf[i];
                        if (str_buf[j] == '\n' || i == read_count - 1) {
                            str_buf[j] = '\0';
                            sprintf(write_buf, "client %d: %s\n", array_fd[sock], str_buf);
                            send_all(sock);
                            j = -1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}