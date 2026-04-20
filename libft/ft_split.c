/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 00:46:39 by dchernik          #+#    #+#             */
/*   Updated: 2026/01/11 16:56:07 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	count_words(char const *s, char delim);
static int		split_alg_loop(char ***r, char const *str, char c, size_t *cnt);
static char		*split_get_word(char ***r, char const *str, size_t s, size_t f);

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	wcnt;

	wcnt = 0;
	res = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (res == NULL)
		return (NULL);
	if (!split_alg_loop(&res, s, c, &wcnt))
		return (NULL);
	return (res);
}

static size_t	count_words(char const *s, char delim)
{
	size_t	i;
	size_t	wnum;

	i = 0;
	wnum = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] == delim || s[i] == '\0')
			if (i > 0 && s[i - 1] != delim)
				wnum++;
		i++;
	}
	return (wnum);
}

static int	split_alg_loop(char ***res, char const *str, char c, size_t *wcnt)
{
	size_t	s;
	size_t	f;

	s = 0;
	f = 0;
	while (f <= ft_strlen(str))
	{
		if (str[f] == c || str[f] == '\0')
		{
			if (f > 0 && str[f - 1] != c)
			{
				(*res)[(*wcnt)] = split_get_word(res, str, s, f);
				if ((*res)[(*wcnt)] == NULL)
					return (0);
				(*wcnt)++;
			}
			s = f + 1;
		}
		f++;
	}
	(*res)[*wcnt] = NULL;
	return (1);
}

static char	*split_get_word(char ***res, char const *str, size_t s, size_t f)
{
	size_t	i;
	char	*word;

	word = (char *)malloc((f - s + 1) * sizeof(char));
	if (word == NULL)
	{
		split_free(res);
		return (NULL);
	}
	i = 0;
	while (i < f - s)
	{
		word[i] = str[s + i];
		i++;
	}
	word[i] = '\0';
	return (word);
}
