/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dflorenc <dflorenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:28:19 by dflorenc          #+#    #+#             */
/*   Updated: 2021/08/03 13:28:21 by dflorenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;
	char			*mem;

	k = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	mem = ((char *)malloc(sizeof(char) * (i + j + 1)));
	if (!mem)
		return (NULL);
	while (k < (i + j))
	{
		if (k < i)
			mem[k] = s1[k];
		else
			mem[k] = s2[k - i];
		k++;
	}
	mem[k] = '\0';
	return (mem);
}
