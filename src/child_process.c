/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bferdjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 00:19:23 by bferdjan          #+#    #+#             */
/*   Updated: 2025/04/11 00:04:24 by bferdjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	child1(int pipe_fd[2], char **av, char **envp)
{
	int	fd_in;

	fd_in = open(av[1], O_RDONLY);
	if (fd_in < 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit_error("open infile");
	}
	if (dup2(fd_in, STDIN_FILENO) < 0)
		exit_error("dup2 infile");
	if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
		exit_error("dup2 pipe write");
	close(fd_in);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execute_cmd(av[2], envp);
}

void	child2(int pipe_fd[2], char **av, char **envp)
{
	int	fd_out;

	fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit_error("open outfile");
	}
	if (dup2(pipe_fd[0], STDIN_FILENO) < 0)
		exit_error("dup2 pipe read");
	if (dup2(fd_out, STDOUT_FILENO) < 0)
		exit_error("dup2 outfile");
	close(fd_out);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execute_cmd(av[3], envp);
}
