/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dflorenc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:22:19 by dflorenc          #+#    #+#             */
/*   Updated: 2021/04/25 10:40:40 by dflorenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_substr_cpy(char *mem, char const *s, unsigned int st, size_t l)
{
	unsigned int	i;
	size_t			k;

	i = 0;
	k = 0;
	while (s[i])
	{
		if ((i >= st) && (k < l))
		{
			mem[k] = s[i];
			k++;
		}
		i++;
	}
	mem[k] = '\0';
	return (mem);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	size_t			k;
	char			*mem;

	i = 0;
	k = 0;
	if (!s)
		return (NULL);
	if (len > ((ft_strlen(s) + 1) - start))
		len = ft_strlen(s) - start;
	if ((unsigned int)ft_strlen(s) < start)
		len = 0;
	mem = ((char *)malloc(sizeof(char) * (len + 1)));
	if (mem == 0)
		return (0);
	mem = ft_substr_cpy(mem, s, start, len);
	return (mem);
}
