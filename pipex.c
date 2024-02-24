/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:38:48 by danevans          #+#    #+#             */
/*   Updated: 2024/02/24 10:38:51 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*int main(int ac, char *av[], char *envp[])
{
    if (ac == 5)
    {
    int    pipefd[2];
    pid_t   pid1;
    pid_t   pid2;
    int     infile;
    int     outfile;

    if (pipe(pipefd) == -1)
        return(0);
    pid1 = fork();
    if (pid1 == -1)
        return(-1);
    if (pid1 == 0)
    {
       infile = ft_file(av[1], 0);
       if (infile == -1)
            perror("infile couldn't open");
        else
        {
            if (dup2(infile, STDIN_FILENO) == -1)
            {
                perror("dup2(infile) not sucessful");
                exit(0);
            }
            close(infile);
            close(pipefd[0]);
            if (dup2(pipefd[1], STDOUT_FILENO) == -1)
            {
                perror("dup2(pipefd1) nitch sucessful");
                exit(1);
            }
            
            ft_execute(av, envp, 2);
            
            close(pipefd[1]);
            exit(0);
        }
    }
    pid2 = fork();
    if (pid2 == -1)
        return(-1);
    if (pid2 == 0)
    {
        close(pipefd[1]);
        if (dup2(pipefd[0], STDIN_FILENO) == -1)
        {
            perror ("dup2(pipefd0) not sucessful");
            exit(0);
        }
        close(pipefd[0]);
        outfile = ft_file(av[4], 1);
        if (outfile == -1)
        {
            perror ("outfile couldn't open");
            exit (0);
        }
        if (dup2(outfile, STDOUT_FILENO) == -1)
        {
            perror ("dup2(outfile) not sucessful");
            exit(0);
        }
        close(outfile);
        ft_execute(av, envp, 3);
    }
        close(pipefd[0]);
        close(pipefd[1]);
        close(infile);
        waitpid(pid1, NULL, 0);
        waitpid(pid2, NULL, 0);
    }
else
    bad_arg(0);
return 0;
}
*/
int main(int ac, char *av[], char *envp[]) {
    if (ac == 5) {
        //exit(1);
        int pipefd[2];
        pid_t pid1;
        pid_t pid2;
        int infile;
        int outfile;

        if (pipe(pipefd) == -1) {
            error();
        }

        pid1 = fork();
        if (pid1 == -1) {
            error();
        }
        //exit(1);
        if (pid1 == 0) {
            infile = ft_file(av[1], 0);
            if (infile == -1) {
                error();
            }
            if (dup2(infile, STDIN_FILENO) == -1) {
                error();
            }
            close(infile);
            close(pipefd[0]);
            if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
                error();
            }
            ft_execute(av, envp, 2);
                //error();
            close(pipefd[1]);
            exit(EXIT_SUCCESS);
        }

        pid2 = fork();
        if (pid2 == -1) {
            error();
        }
        if (pid2 == 0) {
            close(pipefd[1]);
            if (dup2(pipefd[0], STDIN_FILENO) == -1) {
                error();
            }
            close(pipefd[0]);
            outfile = ft_file(av[4], 1);
            if (outfile == -1) {
                error();
            }
            if (dup2(outfile, STDOUT_FILENO) == -1) {
                error();
            }
            close(outfile);
            ft_execute(av, envp, 3);
            exit(0);
        }

        close(pipefd[0]);
        close(pipefd[1]);
        //waitpid(pid1, NULL, 0);
        //waitpid(pid2, NULL, 0);
    } else {
        bad_arg(0); // Print usage message
        return 1;
    }

    return 0;
}
