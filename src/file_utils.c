/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bferdjan <bferdjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:50:01 by bferdjan          #+#    #+#             */
/*   Updated: 2025/05/22 03:38:37 by bferdjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	open_input_file(char *file, int pipe_fd[2])
{
	int	fd_in;

	fd_in = open(file, O_RDONLY);
	if (fd_in < 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		write(2, "pipex: ", 7);
		perror("open infile");
		exit(1);
	}
	return (fd_in);
}

int	open_output_file(char *file, int pipe_fd[2])
{
	int	fd_out;

	fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		write(2, "pipex: ", 7);
		perror("open outfile");
		exit(1);
	}
	return (fd_out);
}

void	handle_dup_error(int fd_in, int pipe_fd[2], char *msg)
{
	close(fd_in);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	perror(msg);
	exit(1);
}

void	handle_dup_out_error(int fd_out, int pipe_fd[2], char *msg)
{
	close(fd_out);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	perror(msg);
	exit(1);
}
