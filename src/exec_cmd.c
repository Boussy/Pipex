/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bferdjan <bferdjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 00:19:16 by bferdjan          #+#    #+#             */
/*   Updated: 2025/05/22 03:12:42 by bferdjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	free_and_exit(char **args, char *path, const char *msg,
		int exit_code)
{
	if (args)
		ft_free_array(args);
	if (path)
		free(path);
	perror(msg);
	exit(exit_code);
}

void	execute_cmd(char *cmd, char **envp)
{
	char	**args;
	char	*cmd_path;

	if (ft_strchr(cmd, '\'') || ft_strchr(cmd, '"'))
	{
		write(2, "pipex: quotes are not supported\n", 32);
		exit(127);
	}
	args = ft_split(cmd, ' ');
	if (!args || !args[0])
		free_and_exit(args, NULL, "Command parse error", 126);
	cmd_path = get_path(args[0], envp);
	if (!cmd_path)
		free_and_exit(args, NULL, cmd, 127);
	if (execve(cmd_path, args, envp) == -1)
	{
		write(2, "executing: ", 11);
		perror(args[0]);
		free_and_exit(args, cmd_path, "execve failed", 126);
	}
}
