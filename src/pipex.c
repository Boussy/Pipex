/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bferdjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 00:19:45 by bferdjan          #+#    #+#             */
/*   Updated: 2025/03/13 00:19:47 by bferdjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	create_pipe(int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
		exit_error("pipe");
}

static pid_t	create_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit_error("fork");
	return (pid);
}

void	pipex(char **av, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	create_pipe(pipe_fd);
	pid1 = create_process();
	if (pid1 == 0)
		child1(pipe_fd, av, envp);
	pid2 = create_process();
	if (pid2 == 0)
		child2(pipe_fd, av, envp);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main(int ac, char **av, char **envp)
{
	if (ac != 5)
	{
		write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 36);
		return (1);
	}
	pipex(av, envp);
	return (0);
}
