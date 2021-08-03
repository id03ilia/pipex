/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dflorenc <dflorenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:28:57 by dflorenc          #+#    #+#             */
/*   Updated: 2021/08/03 13:42:17 by dflorenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_files(int argc, char **argv, t_pip	*piped)
{
	if (piped->file_d[0] == -1)
		std_error(1, strerror (errno), argv[1]);
	piped->file_d[1] = open(argv[argc - 1], O_TRUNC | O_WRONLY | O_CREAT, 0666);
	if (piped->file_d[1] == -1)
		std_error(1, strerror (errno), argv[argc - 1]);
}

static void	exec_in_file(t_pip	*piped, char **argv, char **env)
{
	close_prog(piped->file_d[1], piped->fd[0][0]);
	pipex(piped->file_d[0], piped->fd[0][1], argv[2], env);
}

static void	exec_cmd(int *i, t_pip	*piped, char **argv, char **env)
{
	if (pipe(piped->fd[*i]) == -1)
		error(6);
	piped->pid1 = fork();
	if (piped->pid1 < 0)
		std_error(1, strerror(errno), argv[*i + 2]);
	if (!piped->pid1)
	{
		close(piped->fd[*i][0]);
		pipex(piped->fd[*i - 1][0], piped->fd[*i][1], argv[*i + 2], env);
		exit(0);
	}
	close(piped->fd[*i][1]);
	wait(0);
	(*i)++;
}

static void	exec_cmd_out_file(int argc, char **argv, t_pip	*piped, char **env)
{
	int	i;

	close_prog(piped->file_d[0], piped->fd[0][1]);
	wait(NULL);
	i = 1;
	while (i < (argc - 4))
		exec_cmd(&i, piped, argv, env);
	i--;
	piped->pid1 = fork();
	if (!piped->pid1)
	{
		close(piped->fd[i][1]);
		pipex(piped->fd[i][0], piped->file_d[1], argv[argc - 2], env);
	}
	close_prog(piped->fd[i][0], piped->file_d[1]);
	wait(0);
}

int	main(int argc, char **argv, char **env)
{
	t_pip	piped;

	if (argc > 4)
	{
		piped.file_d[0] = open(argv[1], O_RDONLY);
		init_files(argc, argv, &piped);
		init_fd(&piped, argc);
		if (pipe(piped.fd[0]) == -1)
			error(6);
		piped.pid1 = fork();
		if (piped.pid1 < 0)
			std_error(1, strerror(errno), argv[2]);
		if (!piped.pid1)
			exec_in_file(&piped, argv, env);
		else
			exec_cmd_out_file(argc, argv, &piped, env);
	}
	else
		error(10);
	free_mass_i(piped.fd, argc - 4);
	waitpid(piped.pid1, NULL, 0);
	return (0);
}
