/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bferdjan <bferdjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 00:19:45 by bferdjan          #+#    #+#             */
/*   Updated: 2025/05/22 03:38:37 by bferdjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int	check_input_file(char *filename)
{
	if (access(filename, F_OK) == -1)
	{
		write(2, "pipex: ", 7);
		perror(filename);
		return (1);
	}
	return (0);
}

/*
 * La priorité est donnée au statut de la deuxième commande
 */
static int	get_exit_status(int status1, int status2)
{
	if (WIFEXITED(status2))
		return (WEXITSTATUS(status2));
	else if (WIFSIGNALED(status2))
		return (128 + WTERMSIG(status2));
	else if (WIFEXITED(status1))
		return (WEXITSTATUS(status1));
	else if (WIFSIGNALED(status1))
		return (128 + WTERMSIG(status1));
	else
		return (EXIT_FAILURE);
}

int	pipex(char **av, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status1;
	int		status2;

	if (check_input_file(av[1]))
		return (1);
	create_pipe(pipe_fd);
	pid1 = create_process();
	if (pid1 == 0)
		child1(pipe_fd, av, envp);
	pid2 = create_process();
	if (pid2 == 0)
		child2(pipe_fd, av, envp);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	return (get_exit_status(status1, status2));
}

int	main(int ac, char **av, char **envp)
{
	if (ac != 5)
	{
		write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 36);
		return (1);
	}
	return (pipex(av, envp));
}
