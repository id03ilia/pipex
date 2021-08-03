/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mas.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dflorenc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 12:09:48 by dflorenc          #+#    #+#             */
/*   Updated: 2021/08/03 12:09:52 by dflorenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(int i)
{
	if (i == 1)
		write(1,
			  "Error\n-count arg., format: ./pipex file1 cmd1 cmd2 file2\n", 57);
	if (i == 2)
		write(1, "Error\n-memory fail\n", 19);
	if (i == 3)
		write(1, "Error\n-read fail\n", 17);
	if (i == 6)
		write(1, "Error\n-pipe\n", 12);
	if (i == 8)
		write(1, "Error\n-cant open TEST_OUT\n", 26);
	if (i == 9)
		write(1, "Error\n-command\n", 15);
	if (i == 10)
		write(1,
			  "Error\n-count arg., format: ./pipex file1 cmd1 cmd2 .. cmdN file2"
			  "\n", 65);
	exit(1);
}

void	std_error(int fd, char *str_err, char *name)
{
	write(fd, str_err, ft_strlen(str_err));
	write(fd, ": ", 2);
	write(fd, name, ft_strlen(name));
	write(fd, "\n", 1);
	exit(1);
}

void	close_prog(int file_d, int d)
{
	close(file_d);
	close(d);
}

void	free_mass(char **mas)
{
	int	y;

	y = 0;
	if (mas)
	{
		while (mas[y])
		{
			free(mas[y]);
			mas[y] = NULL;
			y++;
		}
		free(mas);
		mas = NULL;
	}
}

void	free_mass_i(int **mas, int n)
{
	int	y;

	y = 0;
	if (mas)
	{
		while (n--)
		{
			free(mas[y]);
			mas[y] = NULL;
			y++;
		}
		free(mas);
		mas = NULL;
	}
}
