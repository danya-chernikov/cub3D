/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:43:11 by dchernik          #+#    #+#             */
/*   Updated: 2024/10/03 02:37:36 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	g_lpos(size_t *lpos, char const *s1, char const *set);
static void	g_rpos(size_t *rpos, size_t *lpos, char const *s1, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	lpos;
	size_t	rpos;
	size_t	j;
	char	*res_str;

	if (s1 == NULL || set == NULL || *s1 == '\0')
		return (ft_strdup(""));
	g_lpos(&lpos, s1, set);
	g_rpos(&rpos, &lpos, s1, set);
	res_str = (char *)malloc((rpos - lpos + 2) * sizeof(char));
	if (res_str == NULL)
		return (NULL);
	j = lpos;
	while (j <= rpos)
	{
		res_str[j - lpos] = s1[j];
		j++;
	}
	res_str[j - lpos] = '\0';
	return (res_str);
}

static void	g_lpos(size_t *lpos, char const *s1, char const *set)
{
	size_t	j;
	size_t	f;
	size_t	set_len;
	size_t	s1_len;

	set_len = ft_strlen(set);
	s1_len = ft_strlen(s1);
	*lpos = 0;
	while (*lpos < s1_len)
	{
		f = 0;
		j = 0;
		while (j < set_len)
		{
			if (s1[*lpos] == set[j])
			{
				f = 1;
				break ;
			}
			j++;
		}
		if (!f)
			break ;
		(*lpos)++;
	}
}

static void	g_rpos(size_t *rpos, size_t *lpos, char const *s1, char const *set)
{
	size_t	j;
	size_t	f;
	size_t	set_len;

	set_len = ft_strlen(set);
	*rpos = ft_strlen(s1) - 1;
	while (*rpos > *lpos)
	{
		f = 0;
		j = 0;
		while (j < set_len)
		{
			if (s1[*rpos] == set[j])
			{
				f = 1;
				break ;
			}
			j++;
		}
		if (!f)
			break ;
		(*rpos)--;
	}
}
