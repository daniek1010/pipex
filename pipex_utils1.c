/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 08:50:30 by danevans          #+#    #+#             */
/*   Updated: 2024/02/24 10:11:01 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_file(char *file, int mode)
{
	int	file_fd;

	if (mode == 0)
	{
		file_fd = open(file, O_RDONLY);
		if (file_fd == -1)
		{
			error();
		}
		else
			return (file_fd);
	//(file_fd);
	}
	else if (mode == 1)
	{
		file_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file_fd == -1)
		{
			error();
		}
		else
			return (file_fd);
	}
	error();
}

int	ft_execute(char *av[], char *envp[], int x)
{
	char	*path;
	char	**cmd;

	path = ft_access(av[x], envp, x);
	//if (path == NULL)
	//{
		//error();
	//}
	cmd = ft_split(av[x], ' ');
	if (execve(path, cmd, envp) == -1)
	{

		//bad_arg(x);
		free(cmd);
		free(path);
		//return (0);
		error();
		//exit(1);
		
	}
	return(1);
}

char	*ft_access(char *av, char *envp[], int x)
{
	char	**splitted;
	char	*str;
	char	*path;
	char	**cmd;
	int		i;

	splitted = check_path(envp);
	cmd = ft_split(av, ' ');
	i = 0;
	while (splitted[i] != NULL)
	{
		str = ft_strjoin(splitted[i], "/");
		path = ft_strjoin(str, cmd[0]);
		if (access(path, X_OK) == 0)
			break ;
		free(path);
		free(str);
		i++;
	}
	if (splitted[i] == NULL)
	{
		
		error();
	}
	free(str);
	ft_cleaner(splitted);
	ft_cleaner(cmd);
	return (path);
}

char	**check_path(char *envp[])
{
	int		i;
	char	**splitted;

	i = 0;
	splitted = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			splitted = ft_split(envp[i] + 5, ':');
			break ;
		}
		i++;
	}
	return (splitted);
}

void	*ft_cleaner(char *str[])
{
	int		i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}
