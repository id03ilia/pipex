# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>
# include <sys/wait.h>
# include <string.h>
# include <ftw.h>

int main(void)
{
	pid_t  pid;
	int 	in;
	int 	out;
	char *cat[3] = {"/bin/cat", "-e", NULL};
	int fd[2];
	int fd1[2];

	in = open("main.c", O_RDONLY);
	out = open("new.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);

	pipe(fd);

	pid = fork();
	if (!pid)
	{
		close(fd[0]);
		dup2(in, 0);
		dup2(fd[1], 1);
		execve(cat[0], cat, NULL);
		exit(0);
	}
	else
	{

		close(in);
		close(fd[1]);
		wait(0);
		pipe(fd1);
		pid = fork();
		if (!pid)
		{
			close(fd1[0]);
			dup2(fd[0], 0);
			dup2(fd1[1], 1);
			execve(cat[0], cat, NULL);
			exit(0);
		}
		close(fd1[1]);
		wait(0);
		pid = fork();
		if (!pid)
		{
			close(fd1[1]);
			dup2(fd1[0], 0);
			dup2(out, 1);
			execve(cat[0], cat, NULL);
			exit(0);
		}
		close(fd1[0]);
		close(out);
	wait(0);
	}
	return (0);
}