/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:42:37 by dchernik          #+#    #+#             */
/*   Updated: 2024/10/02 02:58:23 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	g_str_lens(size_t *l1, size_t *l2, char const *s1, char const *s2);
static void	strjoin_alg(char *res_str, char const *s1, char const *s2);

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res_str;
	size_t	len_s1;
	size_t	len_s2;

	g_str_lens(&len_s1, &len_s2, s1, s2);
	res_str = (char *) malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (res_str == NULL)
		return (NULL);
	strjoin_alg(res_str, s1, s2);
	return (res_str);
}

static void	g_str_lens(size_t *ls1, size_t *ls2, char const *s1, char const *s2)
{
	*ls1 = ft_strlen(s1);
	*ls2 = ft_strlen(s2);
}

static void	strjoin_alg(char *res_str, char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	g_str_lens(&len_s1, &len_s2, s1, s2);
	while (i < len_s1)
	{
		res_str[i] = s1[i];
		i++;
	}
	while (j < len_s2)
	{
		res_str[i] = s2[j];
		i++;
		j++;
	}
	res_str[i] = '\0';
}
