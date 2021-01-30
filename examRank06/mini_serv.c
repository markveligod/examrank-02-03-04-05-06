#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <stdlib.h>
#include <stdio.h>

int max_fd;
int g_number;

typedef struct s_client
{
    int fd;
    int id;
    struct s_client *next;
} t_client;

void init_set(int fd, fd_set *set_read, t_client *cl)
{
    FD_ZERO(set_read);
    max_fd = fd;
    t_client * temp = cl;
    while (temp)
    {
        FD_SET(temp->fd, set_read);
        if (max_fd < temp->fd)
            max_fd = temp->fd;
        temp = temp->next;
    }
    FD_SET(fd, set_read);
}

int add_client(int fd, t_client **cl)
{
    t_client *new;

    if (!(new = malloc(sizeof(t_client))))
    {
        close(fd);
		write(2, "Fatal error\n", strlen("Fatal error\n"));
        exit(1);
    }
    new->fd = fd;
    new->id = g_number++;
    new->next = NULL;

    if (!(*cl))
    {
        (*cl) = new;
    }
    else
    {
        t_client *temp = *cl;
        while (temp->next)
            temp = temp->next;
        temp->next = new;
    }
    return (new->id);
}

void send_all(t_client *cl, int fd, char *str)
{
    t_client *temp = cl;
    while (temp)
    {
        if (temp->fd != fd)
            send(temp->fd, str, strlen(str), 0);
        temp = temp->next;
    }
    write(1, str, strlen(str));
}

int remove_client(t_client **cl, int fd)
{
    t_client *temp = *cl;
    int id;

    if (temp && temp->fd == fd)
    {
        (*cl) = temp->next;
		id = temp->id;
		close(temp->fd);
		free(temp);
    }
    else if (temp)
    {
        t_client * prev;
        while (temp && temp->next && temp->next->fd != fd)
            temp = temp->next;
        prev = temp;
        temp = temp->next;
        prev->next = temp->next;
        id = temp->id;
        close(temp->fd);
        free(temp);
    }
    return (id);   
}


int main(int ac, char **av) 
{
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;
    char *buff;
    char str[5000];

    int port;
    fd_set set_read;
    t_client *cl = NULL;
    int result;
    int id;
    struct timeval tv;

    if (ac != 2)
    {
        write(2, "Wrong number of arguments\n", strlen("Wrong number of arguments\n"));
        exit(1);
    }

    port = atoi(av[1]);
    if (port <= 0)
    {
        write(2, "Fatal error\n", strlen("Fatal error\n"));
        exit(1);
    }

	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) 
    {
		write(2, "Fatal error\n", strlen("Fatal error\n"));
        exit(1); 
	} 
	 
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(port); 
  
	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) 
    {
        close(sockfd);
		write(2, "Fatal error\n", strlen("Fatal error\n"));
        exit(1);
	}

	if (listen(sockfd, 10) != 0)
    {
		close(sockfd);
		write(2, "Fatal error\n", strlen("Fatal error\n"));
        exit(1);
	}

    if ((buff = malloc(4096)) == NULL)
	{
		write(2, "Fatal error\n", 12);
		close(sockfd);
		exit(1);
	}

	len = sizeof(cli);
    g_number = 0;
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    while(1)
    {
        // write(1, "Debug loop\n", strlen("Debug loop\n"));
        bzero(buff, 4096);
        bzero(str, 5000);
        init_set(sockfd, &set_read, cl);
		result = select(max_fd + 1, &set_read, NULL, NULL, NULL);
		if (result > 0)
		{
			if (FD_ISSET(sockfd, &set_read)) // New connection
			{
				connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
				if (connfd >= 0)
				{
					id = add_client(connfd, &cl);
					if (max_fd < connfd)
						max_fd = connfd;
					sprintf(str, "server: client %d just arrived\n", id);
					send_all(cl, connfd, str);
				}
                //debug
                printf("DEBUG new connection\n");
                t_client *temp = cl;
                while (temp)
                {
                    printf("Id: %d FD: %d\n", temp->id, temp->fd);
                    temp = temp->next;
                }
			}
            else
            {
                t_client *temp = cl;
                while (temp)
                {
                    connfd = temp->fd;
                    id = temp->id;
                    temp = temp->next;
                    if (FD_ISSET(connfd, &set_read))
                    {
                        result = recv(connfd, buff, 4096, 0);
                        printf("Result: %d STR: %s", result, buff);
                        if (result == 0)
                        {  //disconnect
                            id = remove_client(&cl, connfd);
                            sprintf(str, "server: client %d just left\n", id);
							send_all(cl, connfd, str);
                        }
                        else if (result > 0)
                        {
                            sprintf(str, "client %d: %s", id, buff);
							send_all(cl, connfd, str);
                        }
                    }
                }
            }
        }
    }
}
