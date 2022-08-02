#include "pipex.h"

void	close_pipes(int fd[][2])
{
	close(*fd[0]);
	close(*fd[1]);
}

void	child_process(t_pipex p, int fd[][2], int i, char **argv, int argc, char **envp)
{
	int c;

	c = 0;
	if (i == 0)
	{
		close(fd[i][0]);
		while (c++ < (argc - 3))
			close_pipes(&fd[c]);
		dup2(p.infile, 0);
		dup2(fd[i][1], 1);
	}
	else if (i == argc - 4)
	{
		close(fd[i-1][1]);
		while (c++ < (i - 1))
			close_pipes(&fd[c]);
		dup2(fd[i-1][0], 0);
		dup2(p.outfile, 1);
	}
	else
	{
		close(fd[i][0]);
		close(fd[i-1][1]);
		while (c++ < (i - 1))
			close_pipes(&fd[c]);
		dup2(fd[i-1][0], 0);
		dup2(fd[i][1], 1);
	}
	execve(ft_find_path(argv[i+2], envp), ft_split(argv[i+2], ' '), envp);
}

void	multi_pipex(t_pipex p, int argc, char **argv, char **envp)
{
	int	fd[argc-4][2];
	int	id[argc-3];
	int	i;
	
	i = 0;
	while (i < (argc - 4))
	{
		if (pipe(fd[i++]) < 0)
			perror("pipe() error");
	}
	i = 0;
	while (i < (argc - 3))
	{
		id[i] = fork();
		if (id[i] < 0)
			perror("fork() error");
		else if (id[i] == 0)
			child_process(p, fd, i, argv, argc, envp);
		i++;
	}
	waitpid(id[i], NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;

	if (argc > 4)
	{
		p.infile = open(argv[1], O_RDONLY);
		p.outfile = open(argv[argc - 1], O_CREAT | O_CREAT | O_WRONLY, 0644);
		if (p.infile < 0 || p.outfile < 0)
			perror("file error");
		multi_pipex(p, argc, argv, envp);
		close(p.infile);
		close(p.outfile);
	}
	else
		perror("Wrong number of arguments");
	return (0);
}