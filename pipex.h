/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dflorenc <dflorenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:30:47 by dflorenc          #+#    #+#             */
/*   Updated: 2021/08/03 13:30:49 by dflorenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>
# include <sys/wait.h>
# include <string.h>
# include <ftw.h>

typedef struct s_list
{
	int				file_d[2];
	int				d[2];
	int				d2[2];
	int				**fd;
	pid_t			pid1;
	pid_t			pid2;
}				t_pip;

char	**ft_split(char const *s, char c);
int		ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_putstr(char *s, int fd);
char	*get_path(char *cmd, char **env);
char	*ft_strjoin(char const *s1, char const *s2);
void	free_mass(char **mas);
void	error(int i);
void	std_error(int fd, char *str_err, char *name);
void	close_prog(int file_d, int d);
void	free_mass_i(int **mas, int n);
void	pipex(int fd1, int fd2, char *cmd1, char **env);
void	init_fd(t_pip *piped, int argc);

#endif
