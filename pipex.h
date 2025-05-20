/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bferdjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 00:20:01 by bferdjan          #+#    #+#             */
/*   Updated: 2025/03/13 00:20:03 by bferdjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// libc
# include <fcntl.h>     //O_RDONLY, O_WRONLY, O_CREAT, etc. utilisés dans open()
# include <stdio.h>     //perror()
# include <stdlib.h>    //malloc(), free(), exit()
# include <string.h>    //strerror() (dans perror())
# include <sys/types.h> //pid_t, size_t
# include <sys/wait.h>  //wait() et waitpid()
# include <unistd.h>    //access(), execve(), dup(), dup2(), pipe(), fork(),
//                        write(), read(), close()

// process
void	pipex(char **av, char **envp);
void	child1(int pipe_fd[2], char **av, char **envp);
void	child2(int pipe_fd[2], char **av, char **envp);
void	execute_cmd(char *cmd, char **envp);

// path
char	*get_path(char *cmd, char **envp);

// utils
char	**ft_split(const char *s, char c);
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_free_array(char **arr);

// error
void	exit_error(const char *msg);

#endif
