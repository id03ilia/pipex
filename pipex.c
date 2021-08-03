/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dflorenc <dflorenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:29:09 by dflorenc          #+#    #+#             */
/*   Updated: 2021/08/03 13:40:58 by dflorenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_in(t_pip piped, char *cmd1, char **env)
{
	char	*path;
	char	**cmd_f;

	dup2(piped.file_d[0], 0);
	dup2(piped.d[1], 1);
	cmd_f = ft_split(cmd1, ' ');
	if (cmd_f == NULL)
		error(2);
	path = get_path(cmd_f[0], env);
	if (path)
	{
		if (execve(path, cmd_f, env) == -1)
			std_error(1, strerror (errno), cmd_f[0]);
		free(path);
	}
	else
	{
		write(2, "pipex: command not found: ", 26);
		ft_putstr(cmd_f[0], 2);
		write(2, "\n", 1);
		free_mass(cmd_f);
		exit (1);
	}
	free_mass(cmd_f);
}

void	pipex_out(t_pip piped, char *cmd2, char **env)
{
	char	*path;
	char	**cmd_f;

	dup2(piped.file_d[1], 1);
	dup2(piped.d[0], 0);
	cmd_f = ft_split(cmd2, ' ');
	if (cmd_f == NULL)
		error(2);
	path = get_path(cmd_f[0], env);
	if (path)
	{
		if (execve(path, cmd_f, env) == -1)
			std_error(1, strerror (errno), cmd_f[0]);
		free(path);
	}
	else
	{
		write(2, "pipex: command not found: ", 26);
		ft_putstr(cmd_f[0], 2);
		write(2, "\n", 1);
		free_mass(cmd_f);
		exit (1);
	}
	free_mass(cmd_f);
}

void	ft_pipex(t_pip piped, char *cmd1, char *cmd2, char **env)
{
	piped.pid1 = fork();
	if (piped.pid1 < 0)
		std_error(1, strerror (errno), cmd1);
	if (piped.pid1 == 0)
	{
		close_prog(piped.file_d[1], piped.d[0]);
		pipex_in(piped, cmd1, env);
	}
	piped.pid2 = fork();
	if (piped.pid2 < 0)
		std_error(1, strerror (errno), cmd2);
	if (piped.pid2 == 0)
	{
		wait(NULL);
		close_prog(piped.file_d[0], piped.d[1]);
		pipex_out(piped, cmd2, env);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_pip	piped;

	if (argc == 5)
	{
		piped.file_d[0] = open(argv[1], O_RDONLY);
		if (piped.file_d[0] == -1)
			std_error(1, strerror (errno), argv[1]);
		piped.file_d[1] = open(argv[4], O_TRUNC | O_WRONLY | O_CREAT, 0666);
		if (piped.file_d[1] == -1)
			std_error(1, strerror (errno), argv[4]);
		if (pipe(piped.d) == -1)
			error(6);
		else
			ft_pipex(piped, argv[2], argv[3], env);
	}
	else
		error(1);
	close_prog(piped.file_d[1], piped.d[0]);
	close_prog(piped.file_d[0], piped.d[1]);
	waitpid(piped.pid1, NULL, 0);
	waitpid(piped.pid2, NULL, 0);
	return (0);
}
