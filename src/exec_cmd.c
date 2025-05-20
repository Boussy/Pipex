/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bferdjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 00:19:16 by bferdjan          #+#    #+#             */
/*   Updated: 2025/03/13 00:19:18 by bferdjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	free_and_exit(char **args, char *path, const char *msg)
{
	if (args)
		ft_free_array(args);
	if (path)
		free(path);
	perror(msg);
	exit(1);
}

void	execute_cmd(char *cmd, char **envp)
{
	char	**args;
	char	*cmd_path;

	if (ft_strchr(cmd, '\'') || ft_strchr(cmd, '"'))
	{
		write(2, "pipex: quotes are not supported\n", 32);
		exit(1);
	}
	args = ft_split(cmd, ' ');
	if (!args || !args[0])
		free_and_exit(args, NULL, "Command parse error");
	cmd_path = get_path(args[0], envp);
	if (!cmd_path)
		free_and_exit(args, NULL, cmd);
	if (execve(cmd_path, args, envp) == -1)
	{
		write(2, "executing: ", 11);
		perror(args[0]);
		free_and_exit(args, cmd_path, "execve failed");
	}
}
