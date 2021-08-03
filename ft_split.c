/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dflorenc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 12:05:51 by dflorenc          #+#    #+#             */
/*   Updated: 2021/04/26 12:05:54 by dflorenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_count_strok(char const *s, char c)
{
	int	i;
	int	c_str;
	int	rez_str;

	i = 0;
	rez_str = 0;
	c_str = 0;
	while (s[i])
	{
		if (s[i] && s[i] != c)
			c_str++;
		if ((s[i + 1] == c || s[i + 1] == '\0') && s[i] != c && c_str > 0)
		{
			rez_str = rez_str + 1;
			c_str = 0;
		}
		i++;
	}
	return (rez_str);
}

static char	**ft_cpy_mall_free(char **res, int r )
{
	while (r >= 0)
	{
		free (res[r]);
		r--;
	}
	free (res);
	res = NULL;
	return (res);
}

static char	**ft_cpy_strok_mall(char **res, char const *s, char c, int strok)
{
	int		i;
	int		r;
	size_t	wrd;

	i = 0;
	r = 0;
	wrd = 0;
	while (s[i])
	{
		if (s[i] != c)
			wrd++;
		if ((s[i + 1] == c || s[i + 1] == '\0') && wrd > 0 && r <= strok)
		{
			res[r] = ft_substr(s, i - (wrd - 1), wrd);
			if (!res)
			{
				res = ft_cpy_mall_free(res, r);
				return (res);
			}
			wrd = 0;
			r++;
		}
		i++;
	}
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	strok;

	if (!s)
		return (NULL);
	strok = ft_count_strok(s, c);
	res = (char **)malloc(sizeof(char *) * (strok + 1));
	if (!res)
		return (NULL);
	res = ft_cpy_strok_mall(res, s, c, strok);
	res[strok] = (void *)0;
	return (res);
}
