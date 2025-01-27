/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atazzit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:17:52 by atazzit           #+#    #+#             */
/*   Updated: 2025/01/25 15:17:55 by atazzit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_cmd_path(char *cmd, char **envp)
{
	char	*cmd_path;
	char	**path;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	path = ft_split(envp[i] + 5, ':');
	if (!path)
		return (NULL);
	cmd_path = access_cmd_path(cmd, path);
	return (cmd_path);
}

char	*access_cmd_path(char *cmd, char **path)
{
	char	*temp;
	char	*full;
	int		i;

	i = 0;
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		if (!temp)
			break ;
		full = ft_strjoin(temp, cmd);
		if (!full)
			break ;
		if (access(full, X_OK) == 0)
			return (free(temp), free_split(path), full);
		i++;
		free(full);
		free(temp);
	}
	free_split(path);
	return (NULL);
}

void	process(int child, char **av, char **envp)
{
	char	**args;
	char	*path;

	args = ft_split(av[child], ' ');
	if (!args)
	{
		free_split(args);
		ft_error("Split failed");
	}
	path = get_cmd_path(args[0], envp);
	if (!path)
	{
		free_split(args);
		perror("NO PATH");
		exit(127);
	}
	exec_cmd(path, args, envp);
}

void	exec_cmd(char *path, char **args, char **envp)
{
	int	i;

	i = execve(path, args, envp);
	if (i == -1)
	{
		free(path);
		free_split(args);
		ft_error("EXECVE ERROR");
	}
}
