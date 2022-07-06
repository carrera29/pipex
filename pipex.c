
#include "pipex.h"

void	child_process(t_pipex p, char *cmd, char *envp[])
{
	if (!cmd || !envp)
		perror("something is missing");
	if (p.i == 0)
	{
		close(p.pipe_1_[0]);
		dup2(p.infile, 0);
		dup2(p.pipe_1_[1], 1);
		close(p.pipe_1_[1]);
	}
	else
	{
		dup2(p.pipe_1_[0], 0);
		dup2(p.outfile, 1);	
	}
	execve(ft_find_path(cmd, envp), ft_split(cmd, ' '), envp);
}

void	ft_multi_pipex(t_pipex p, int argc, char **argv, char **envp)
{
	static int	n;

	if (p.id_child_1 == 0)
	{
		n = 2;
		close(p.pipe_1_[0]);
		close(p.pipe_2_[1]);
		dup2(p.infile, 0);
		dup2(p.pipe_1_[1], 1);
		execve(ft_find_path(argv[n], envp), ft_split(argv[n], ' '), envp);
		dup2(p.pipe_2_[0], p.infile);
		if (n == (argc -2))
			dup2(p.outfile, p.pipe_1_[1]);
		execve(ft_find_path(argv[n], envp), ft_split(argv[n], ' '), envp);
		n++;
		close(p.pipe_1_[1]);
		close(p.pipe_2_[0]);
	}
	else
	{
		close(p.pipe_1_[1]);
		close(p.pipe_2_[0]);
		p.id_child_2 = fork();
		if (p.id_child_2 < 0)
			perror ("fork(2) error");
		else if (p.id_child_2 == 0)
		{
			dup2(p.pipe_1_[0], 0);
			dup2(p.pipe_2_[1], 1);
			if (n == (argc -2))
				dup2(p.outfile, p.pipe_2_[1]);
			execve(ft_find_path(argv[n], envp), ft_split(argv[n], ' '), envp);
			n++;
		}
		close(p.pipe_1_[0]);
		close(p.pipe_2_[1]);
	}
	waitpid(p.id_child_1, NULL, 0);
	waitpid(p.id_child_2, NULL, 0);
}

void	ft_pipex(t_pipex p, char **argv, char **envp)
{
	p.i = 0;
	if (p.id_child_1 == 0)
		child_process(p, argv[2], envp);
	else
	{
		close(p.pipe_1_[1]);
		p.i++;
		p.id_child_2 = fork();
		if (p.id_child_2 < 0)
			perror ("fork(2) error");
		else if (p.id_child_2 == 0)
			child_process(p, argv[3], envp);
		close(p.pipe_1_[0]);
	}
	waitpid(p.id_child_1, NULL, 0);
	waitpid(p.id_child_2, NULL, 0);
}

int main(int argc, char **argv, char **envp)
{
	t_pipex p;

	if (argc > 4)
	{
		p.infile = open(argv[1], O_RDONLY);
		p.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_WRONLY, 0644);
		if (p.infile < 0 || p.outfile < 0)
			perror ("file error");
		if (pipe(p.pipe_1_) == -1)
			perror ("pipe error");
		p.id_child_1 = fork();
		if (p.id_child_1 == -1)
			perror ("pipe fork(1)");
	}
	if (argc == 5)
		ft_pipex(p, argv, envp);
	else if (argc > 5)
	{
		if (pipe(p.pipe_2_) == -1)
			perror ("pipe(2) error");
		ft_multi_pipex(p, argc, argv, envp);
	}
	return (0);
}