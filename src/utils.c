/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bferdjan <bferdjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:40:01 by bferdjan          #+#    #+#             */
/*   Updated: 2025/05/22 03:38:37 by bferdjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	create_pipe(int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
		exit_error("pipe");
}

pid_t	create_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit_error("fork");
	return (pid);
}
