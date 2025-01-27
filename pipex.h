/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atazzit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:18:04 by atazzit           #+#    #+#             */
/*   Updated: 2025/01/25 15:18:06 by atazzit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		input_fd;
	int		output_fd;
	int		pipe_fd[2];
	pid_t	child1;
	pid_t	child2;
	char	**path;
}			t_pipex;

void		ft_error(char *msg);
void		free_split(char **split);
char		*get_cmd_path(char *cmd, char **envp);
char		*access_cmd_path(char *cmd, char **path);
void		first_child_process(t_pipex *p, char **av, char **envp);
void		second_child_process(t_pipex *p, char **av, char **envp);
void		exec_cmd(char *path, char **args, char **envp);
void		process(int child, char **av, char **envp);

#endif
