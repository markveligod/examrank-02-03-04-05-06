#include <stdio.h> //del
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SIDE_OUT	0
#define SIDE_IN		1

#define STDIN		0
#define STDOUT		1
#define STDERR		2

#define TYPE_END	0
#define TYPE_PIPE	1
#define TYPE_BREAK	2

typedef struct s_base
{
    char **argv;
    int size;
	int type;
    struct s_base *next;
} t_base;

int ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void exit_fatal(void)
{
    write(STDERR, "error: fatal\n", 13);
    exit(EXIT_FAILURE);
}

void exit_execve(char *str)
{
    write(STDERR, "error: cannot execute ", 22);
    write(STDERR, str, ft_strlen(str));
    write(STDERR, "\n", 1);
    exit(EXIT_FAILURE);
}

void exit_cd_1(void)
{
    write(STDERR, "error: cd: bad arguments\n", 25);
    exit(EXIT_FAILURE);
}

void exit_cd_2(char *str)
{
    write(STDERR, "error: cd: cannot change directory to ", 40);
    write(STDERR, str, ft_strlen(str));
    write(STDERR, "\n", 1);
    exit(EXIT_FAILURE);
}

char *ft_strdup(char *str)
{
    char *new;
    int size = ft_strlen(str);

    if (!(new = (char *)malloc(sizeof(char) * (size + 1))))
        exit_fatal();
    new[size] = '\0';
    while (--size >= 0)
        new[size] = str[size];
    return (new);
}

void ft_lstadd_back(t_base **ptr, t_base *new)
{
    t_base *temp;

	if (!(*ptr))
		*ptr = new;
	else
	{
		temp = *ptr;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

int size_argv(char **argv)
{
    int i = 0;
    while (argv[i] && strcmp(argv[i], "|") != 0 && strcmp(argv[i], ";") != 0)
        i++;
    return (i);
}

int check_end(char *av)
{
    if (!av)
        return (TYPE_END);
    if (strcmp(av, "|") == 0)
        return (TYPE_PIPE);
    if (strcmp(av, ";") == 0)
        return (TYPE_BREAK);
    return (0);
}

int parser_argv(t_base **ptr, char **av)
{
    int size = size_argv(av);
    t_base *new;

    if (!(new = (t_base *)malloc(sizeof(t_base))))
        exit_fatal();
    if (!(new->argv = (char **)malloc(sizeof(char *) * (size + 1))))
        exit_fatal();
    new->size = size;
    new->argv[size] = NULL;
    while (--size >= 0)
        new->argv[size] = ft_strdup(av[size]);
    new->type = check_end(av[new->size]);
    ft_lstadd_back(ptr, new);
    return (new->size);
}

void cd_cmd(t_base *temp)
{
    int ret;

    if (temp->size > 2)
    {
        exit_cd_1();
        exit(EXIT_FAILURE);
    }
    ret = chdir(temp->argv[1]);
    if (ret < 0)
    {
        exit_cd_2(temp->argv[1]);
        exit(EXIT_FAILURE);
    }
}

void exec_cmd_pipe(t_base *temp, char **env, int size)
{
    pid_t pid;
    int status;
    int fd[2];
    int prev_pipe;
    int i = 0;
    int ret;

    prev_pipe = dup(STDIN_FILENO);
    while (i < size)
    {
        if (i < size - 1)
            pipe(fd);
        pid = fork();
        if (pid < 0)
        {
            exit_fatal();
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) //child
        {
            if (prev_pipe != STDIN_FILENO)
	        {
        		dup2(prev_pipe, STDIN_FILENO);
        		close(prev_pipe);
	        }
            dup2(fd[1], STDOUT_FILENO);
	        close(fd[1]);
            if (strcmp(temp->argv[0], "cd") != 0)
            {
                ret = execve(temp->argv[0], temp->argv, env);
                if (ret < 0)
                {
                    exit_execve(temp->argv[0]);
                    exit(EXIT_FAILURE);
                }
            }
            else
                cd_cmd(temp);
            exit(EXIT_SUCCESS);
        }
        else //parent
        {
            waitpid(pid, &status, WUNTRACED);
            close(prev_pipe);
		    close(fd[1]);
		    prev_pipe = fd[0];
            temp = temp->next;
            i++;
        }
    }
}

void exec_cmd(t_base *temp, char **env)
{
    pid_t pid;
    int status;
    int ret;

    pid = fork();
    if (pid < 0)
    {
        exit_fatal();
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) //child
    {
        if (strcmp(temp->argv[0], "cd") != 0)
        {
            ret = execve(temp->argv[0], temp->argv, env);
            if (ret < 0)
            {
                exit_execve(temp->argv[0]);
                exit(EXIT_FAILURE);
            }
        }
        else
            cd_cmd(temp);
        exit(EXIT_SUCCESS);
    }
    else //parent
        waitpid(pid, &status, WUNTRACED);
}

void sort_cmd(t_base *ptr, char **env)
{
    int size;
    t_base *temp_1;
    t_base *temp_2;

    temp_1 = ptr;
    while (temp_1)
    {
        size = 0;
        if (temp_1 && temp_1->type == 1)
        {
            temp_2 = temp_1;
            while (temp_2 && temp_2->type == 1)
            {
                size++;
                temp_2 = temp_2->next;
            }
            exec_cmd_pipe(temp_1, env, ++size);
            temp_1 = temp_2->next;
        }
        else
        {
            exec_cmd(temp_1, env);
            temp_1 = temp_1->next;
        }
    }
    
}

int main(int ac, char **av, char **env)
{
    t_base *ptr = NULL;
    int i;

    (void)ac;
    i = 1;
    while (av[i])
    {
        i += parser_argv(&ptr, &av[i]);
        if (!av[i])
            break;
        else
            i++;
    }
    if (ptr)
        sort_cmd(ptr, env);

/*
    while (ptr)
    {
        printf("-------------------\n");
        for (i = 0; i < ptr->size; i++)
            printf("%d - %s\n", i, ptr->argv[i]);
        printf("TYPE: %d\n", ptr->type);
        printf("SIZE: %d\n", ptr->size);
        ptr = ptr->next;
    }
*/
    return (0);
}