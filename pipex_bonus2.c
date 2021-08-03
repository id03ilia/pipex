/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dflorenc <dflorenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:29:03 by dflorenc          #+#    #+#             */
/*   Updated: 2021/08/03 13:39:22 by dflorenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(int fd1, int fd2, char *cmd1, char **env)
{
	char	*path;
	char	**cmd_f;

	dup2(fd1, 0);
	dup2(fd2, 1);
	cmd_f = ft_split(cmd1, ' ');
	if (cmd_f == NULL)
		error(2);
	path = get_path(cmd_f[0], env);
	if (path)
	{
		if (execve(path, cmd_f, env) == -1)
			std_error(1, strerror (errno), cmd_f[0]);
	}
	else
	{
		write(2, "pipex: command not found: ", 26);
		ft_putstr(cmd_f[0], 2);
		write(2, "\n", 1);
		free_mass(cmd_f);
		exit (1);
	}
}

void	init_fd(t_pip *piped, int argc)
{
	int	i;

	piped->fd = malloc(sizeof(int *) * (argc - 4));
	if (!piped->fd)
		error (2);
	i = 0;
	while (i < (argc - 4))
	{
		piped->fd[i] = malloc(sizeof(int) * 2);
		if (!piped->fd[i])
			error (2);
		i++;
	}
}
