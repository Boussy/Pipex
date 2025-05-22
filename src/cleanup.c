/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bferdjan <bferdjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 00:19:09 by bferdjan          #+#    #+#             */
/*   Updated: 2025/05/22 03:38:37 by bferdjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	open_files(char *file1, char *file2, int *fd_in, int *fd_out)
{
	*fd_in = open(file1, O_RDONLY);
	if (*fd_in < 0)
	{
		perror("pipex: open infile");
		return (0);
	}
	*fd_out = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd_out < 0)
	{
		perror("pipex: open outfile");
		close(*fd_in);
		return (0);
	}
	return (1);
}

void	close_and_cleanup(int fd_in, int fd_out, int pipe_fd[2])
{
	close(fd_in);
	close(fd_out);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

void	ft_free_array(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

void	exit_error(const char *msg)
{
	write(2, "pipex: ", 7);
	perror(msg);
	exit(EXIT_FAILURE);
}
