/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atazzit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:36:51 by atazzit           #+#    #+#             */
/*   Updated: 2025/01/25 18:36:59 by atazzit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	free_split(char **split)
{
	if (!split)
		return ;
	while (*split)
	{
		free(*split);
		split++;
	}
	free(split);
}

void	first_child_process(t_pipex *p, char **av, char **envp)
{
	close(p->pipe_fd[0]);
	p->input_fd = open(av[1], O_RDONLY);
	if (p->input_fd == -1)
		ft_error("FILE ERROR");
	if (dup2(p->input_fd, STDIN_FILENO) == -1)
		ft_error("Dup2 input pipe error");
	if (dup2(p->pipe_fd[1], STDOUT_FILENO) == -1)
		ft_error("Dup2 pipe error");
	close(p->pipe_fd[1]);
	close(p->input_fd);
	process(2, av, envp);
}

void	second_child_process(t_pipex *p, char **av, char **envp)
{
	close(p->pipe_fd[1]);
	p->output_fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->output_fd == -1)
		ft_error("OUTPUT FILE ERROR");
	if (dup2(p->pipe_fd[0], STDIN_FILENO) == -1)
		ft_error("Dup2 pipe error");
	if (dup2(p->output_fd, STDOUT_FILENO) == -1)
		ft_error("Dup2 output error");
	close(p->pipe_fd[0]);
	close(p->output_fd);
	process(3, av, envp);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	p;
	int		status;

	if (ac != 5 || ft_strncmp(av[2], "", 1) == 0 || ft_strncmp(av[3], "",
			1) == 0)
		ft_error("ARG ERROR");
	if (pipe(p.pipe_fd) == -1)
		ft_error("PIPE ERROR");
	p.child1 = fork();
	if (p.child1 == -1)
		ft_error("FORK ERROR");
	if (p.child1 == 0)
		first_child_process(&p, av, envp);
	p.child2 = fork();
	if (p.child2 == -1)
		ft_error("FORK ERROR");
	if (p.child2 == 0)
		second_child_process(&p, av, envp);
	close(p.pipe_fd[0]);
	close(p.pipe_fd[1]);
	waitpid(p.child1, &status, 0);
	waitpid(p.child2, &status, 0);
	return (WEXITSTATUS(status));
}
