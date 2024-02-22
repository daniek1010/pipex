#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../libft/libft.h"

char *ft_access(char *av, char *envp[]);
char *ft_cleaner(char *str[]);
int ft_file(char *file, int mode);
void ft_execute(char *av[], char *envp[], int x);

int main(int ac, char *av[], char *envp[]) {
    if (ac == 5) {
        int pipefd[2];
        int infile;
        int outfile;
        pid_t pid1;
        pid_t pid2;
        int i;

        //printf("first printing\n");
        if (pipe(pipefd) == -1) {
            perror("pipe");
            return 1;
        }
        pid1 = fork();
        if (pid1 == -1) {
            perror("fork");
            return 1;
        }
        //printf("printing the valueee of pid1 = %d\n", pid1);
        if (pid1 == 0) {
            i = 1;
            infile = ft_file(av[i], 0);
            if (infile == -1) {
                perror("ft_file");
                return 1;
            }
            
           // printf("main infile pid1 value = %d\n", infile);
            //fflush(stdout);
            close(pipefd[0]);
            dup2(infile, STDIN_FILENO);
           //removed from here 
           close(infile);
            dup2(pipefd[1], STDOUT_FILENO);
            
            
           // write(pipefd[1], )
            
            close(pipefd[1]);
            
            ft_execute(av, envp, 2);
            exit(0);
        }
        pid2 = fork();
        if (pid2 == -1) {
            perror("fork");
            return 1;
        }
        
        //printf("print value of pid2 = %d\n", pid2);
        if (pid2 == 0) {
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);
            outfile = ft_file(av[4], 1);
            if (outfile == -1) {

                perror("ft_file");
                return 1;
            }
           // printf("close value in main of checking from pid2 out_file value = %d\n", outfile);
            //fflush(stdout);
            dup2(outfile, STDOUT_FILENO);
           // write(outfile, "checking", 8);
            ft_execute(av, envp, 3);
           // write(outfile, "check", 5);
            close(outfile);
            exit(0);
        }
        close(pipefd[0]);
        close(pipefd[1]);
        waitpid(pid1, NULL, 0);
        //if (pid2 > 0)
        waitpid(pid2, NULL, 0);
    } 
    else {
        printf("FMT > file1.txt cmd1 cmd2 file2.txt \n");
    }
    return 0;
}

int ft_file(char *file, int mode) {
    int fd;
    //mode_t old_unmask = umask(0);
    if (mode == 0) {
        fd = open(file, O_RDONLY);
        if (fd == -1) {
            perror("open");
            return -1;
        } else {
            //printf("function opened value of in_file = %d\n", fd);
            //fflush(stdout);
            return fd;
        }
    } else if (mode == 1) {
        fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
            perror("open");
            return -1;
        } else {
           // printf("function opened value of out_file = %d\n", fd);
           // fflush(stdout);
            return fd;
        }
    }
    //umask(old_unmask);
    return -1;
}

void ft_execute(char *av[], char *envp[], int x) {
    char *path;
    char **cmd;
//printf("value of x%d\n", x);
   // fflush(stdout);
    cmd = ft_split(av[x], ' ');
//printf("cmdpath in execute is cmd%d = %s\n", x , cmd[0]);
    //fflush(stdout);
    path = ft_access(av[x], envp);
    //printf("path of cmd%d path = %s\n", x , path);
   // fflush(stdout);
    if (execve(path, cmd, envp) == -1) {
        perror("execve");
        free(path);
        exit(1);
    }
}

char *ft_access(char *av, char *envp[]) {
    int i = 0;
    char **splitted;
    char *str;
    char *path;
    char **cmd;

    int j = 0;
    cmd = ft_split(av, ' ');

    while (envp[i] != NULL) {
        if (ft_strnstr(envp[i], "PATH", 4) != NULL)
            break;
        i++;
    }
    splitted = ft_split(envp[i] + 5, ':');
    i = 0;
    while (splitted[i] != NULL) {
        str = ft_strjoin(splitted[i], "/");
        path = ft_strjoin(str, cmd[0]);
        if (access(path, X_OK) == 0) {
            break;
        }
        free(path);
        free(str);
        i++;
    }
  //  printf("PATH from acces path = %s\n", path);
   // fflush(stdout);
    free(str);
    ft_cleaner(splitted);
    ft_cleaner(cmd);
    return (path);
}

char *ft_cleaner(char *str[]) {
    int i;

    i = 0;
    while (str[i] != NULL) {
        free(str[i]);
        i++;
    }
    free(str);
    return NULL;
}
