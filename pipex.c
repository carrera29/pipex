
#include "pipex.h"

void	child_1_process(t_pipex p, char *cmd, char *envp[])
{
	if (!cmd || !envp)
		perror("something is missing in process 1");
	close(p.tub[0]);
	dup2(p.infile, 0);
	dup2(p.tub[1], 1);
	close(p.tub[1]);
	execve(ft_find_path(cmd, envp), ft_split(cmd, ' '), envp);
}

void	child_2_process(t_pipex p, char *cmd, char *envp[])
{
	if (!cmd || !envp)
		perror("something is missing in process 1");
	dup2(p.tub[0], 0);
	dup2(p.outfile, 1);
	execve(ft_find_path(cmd, envp), ft_split(cmd, ' '), envp);
}

void	ft_pipex(t_pipex p, int argc, char **argv, char **envp)
{
	if (pipe(p.tub) == -1)
		perror ("pipe error");
	p.id_hijo_1 = fork();
	if (p.id_hijo_1 < 0)
		perror ("fork(1) error");
	else if (p.id_hijo_1 == 0)
		child_1_process(p, argv[2], envp);
	else
	{
		close(p.tub[1]);
		p.id_hijo_2 = fork();
		if (p.id_hijo_2 < 0)
			perror ("fork(2) error");
		else if (p.id_hijo_2 == 0)
			child_2_process(p, argv[3], envp);
		close(p.tub[0]);
	}
	waitpid(p.id_hijo_1, NULL, 0);
	waitpid(p.id_hijo_2, NULL, 0);
}

int main(int argc, char **argv, char **envp)
{
	t_pipex p;

	p.infile = open(argv[1], O_RDONLY);
	p.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (p.infile < 0 || p.outfile < 0)
		perror ("file error");
	ft_pipex(p, argc, argv, envp);
	return (0);
}