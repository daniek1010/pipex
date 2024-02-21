#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include <sys/wait.h>
#include"../libft/libft.h"

char *ft_access(char *av, char *envp[]);
char    *ft_cleaner(char *str[]);
int ft_file(char *file, int mode);
void ft_execute(char *av[], char *envp[]);

int main (int ac, char *av[], char *envp[])
{
    if (ac == 5)
    {
        int pipefd[2];
        int infile;
        int outfile;
        char *path;    
        pid_t   pid1;
        pid_t   pid2;

        if (pipe(pipefd) == -1)
        {
            return 0;
        }
        pid1 = fork();
        if (pid1 == -1)
        {
            return 0;
        }
        if (pid1 == 0)
        {
            infile = ft_file(av[1], 1);
            dup2(infile, STDIN_FILENO);
            close (infile);
            close(pipefd[0]);
            dup2(pipefd[1], STDOUT_FILENO);
            ft_execute(av, envp);
            close(pipefd[1]);
        }
        pid2 = fork();
        if (pid2 == -1)
        {
            return 0;
        }
        if (pid2 == 0)
        {
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            ft_execute(av, envp);
            close(pipefd[0]);
            outfile = ft_file(av[4], 2);
            dup2(outfile, STDOUT_FILENO);
            close (outfile);
        }
        waitpid(pid1, NULL, 0);
        waitpid(pid2, NULL, 0);
       //char *value = ft_access(av[2], envp);
        //printf("The value of envp is %s",value );
        //free(value);
    }
    else
    printf("FMT > file1.txt cmd1 cmd2 file2.txt \n");
    //ft_file(av[1], 1);
    //ft_file(av[4], 2);
    return 0;
}

int ft_file(char *file, int mode)
{
    int in_fd;
    int out_fd;

    if (mode == 1)
    {
        in_fd = open(file, O_RDONLY);
        if (in_fd == -1)
            return 0;
        else
            return(in_fd);
    }
    if (mode == 2)
    {
        out_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC | 0777);
        if (out_fd == -1)
            return 0;
        else 
            return(out_fd);
    }
}

void ft_execute(char *av[], char *envp[])
{ 
    char *path;
    char **cmd;

    cmd = ft_split(av[2], ' ');
    
    path = ft_access(av[2], envp);
    if (execve(path, cmd, envp) == -1)
    {   
        free(path);
        //return ;
    }
}

char *ft_access(char *av, char *envp[])
{
    int i = 0;
    char **splitted;
    char *str;
    char *path;
    char **cmd;

    cmd = ft_split(av, ' ');
    
    while (envp[i] != NULL)
    {
        if (ft_strnstr(envp[i], "PATH", 4) != NULL)
        break;
        i++;
    }
    splitted = ft_split(envp[i] + 5, ':');
    i = 0;
    while(splitted[i] != NULL)
    {
        str = ft_strjoin(splitted[i], "/");
        path = ft_strjoin(str, cmd[0]);
       // printf("the add_patherrr = %s\n \n", path);
        if (access(path, X_OK) == 0)
        {
            //printf("the add_path = %s\n \n", add_path);
            break;
        }
        free(path);
        free(str);
        i++;
    }
    free(str);
    ft_cleaner(splitted);
    ft_cleaner(cmd);
    return (path);
}

char    *ft_cleaner(char *str[])
{
    int i;

    i = 0;
    while(str[i] != NULL)
    {
        free(str[i]);
        i++;
    }
    free(str);
}
