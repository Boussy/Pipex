/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bferdjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 00:19:38 by bferdjan          #+#    #+#             */
/*   Updated: 2025/04/11 00:04:56 by bferdjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*get_word(const char *s, char c)
{
	int		i;
	int		len;
	char	*word;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

static void	free_all(char **arr, int i)
{
	while (i-- > 0)
		free(arr[i]);
	free(arr);
}

char	**ft_split(const char *s, char c)
{
	char	**arr;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	arr = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			arr[i] = get_word(s, c);
			if (!arr[i++])
				return (free_all(arr, i), NULL);
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	arr[i] = NULL;
	return (arr);
}
