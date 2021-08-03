/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dflorenc <dflorenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:28:33 by dflorenc          #+#    #+#             */
/*   Updated: 2021/08/03 13:33:17 by dflorenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i] && n > 0)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static char	*join_cmd(char *path_i, char *cmd)
{
	char	*t;
	char	*path_with_cmd;

	t = ft_strjoin(path_i, "/");
	path_with_cmd = ft_strjoin(t, cmd);
	free(t);
	return (path_with_cmd);
}

static char	*check_path(char **path, char *cmd)
{
	int		i;
	int		a;
	char	*path_w;

	i = 0;
	path_w = NULL;
	while (path[i])
	{
		if (path_w)
			free(path_w);
		path_w = join_cmd(path[i], cmd);
		a = access(path_w, X_OK);
		if (a == 0)
		{
			i = 0;
			break ;
		}
		else
			i++;
	}
	if (i > 0)
		path_w = NULL;
	return (path_w);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*path_good;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			paths = ft_split(env[i] + 5, ':');
			path_good = check_path(paths, cmd);
			if (path_good)
			{
				free_mass(paths);
				return (path_good);
			}
			else
				i++;
		}
		else
			i++;
	}
	free_mass(paths);
	return (0);
}
