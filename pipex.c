
#include "pipex.h"

void	close_all(void)
{
	t_pipex	p;

	close(p.tub[0]);
	close(p.tub[1]);
	close(p.infile);
	close(p.outfile);
}

void	child_1_process(int infile, char *cmd, char *envp[])
{
	t_pipex	p;

	if (!cmd || !envp)
		exit (-1);
	close(p.tub[0]);
	dup2(infile, 0);
	dup2(p.tub[1], 1);
	p.path = ft_find_path(cmd, envp);
	p.split_cmd = ft_split(cmd, ' ');
	execve(p.path, p.split_cmd, envp);
	free(p.path);
	free(p.split_cmd);
	close(p.tub[1]);
}

// void	child_2_process(int outfile, char *cmd, char *envp[])
// {
// 	t_pipex	p;

// 	if (!cmd || !envp)
// 		exit (-1);
// 	dup2(p.tub[0], 0);
// 	dup2(outfile, 1);
// 	p.path = ft_find_path(cmd, envp);
// 	p.split_cmd = ft_split(cmd, ' ');
// 	execve(p.path, p.split_cmd, envp);
// 	free(p.path);
// 	free(p.split_cmd);
// }

int main(int argc, char *argv[], char *envp[])
{
	t_pipex p;

	p.infile = open(argv[1], O_RDONLY, 0000644);
	p.outfile = open(argv[argc -1], O_TRUNC | O_CREAT | O_WRONLY, 0000644);
	if (p.infile < 0 || p.outfile < 0)
		perror ("file error");
	if (pipe(p.tub) == -1)
		perror ("pipe error");
	p.id_hijo_1 = fork();
	if (p.id_hijo_1 < 0)
		perror ("fork() error");
	else if (p.id_hijo_1 == 0)
	{
		child_1_process(p.infile, argv[2], envp);
		close(p.infile);
	}
	else
	{
		close(p.tub[1]);
		p.id_hijo_2 = fork();
		if (p.id_hijo_2 < 0)
			perror ("fork() 2 error");
		else if (p.id_hijo_2 == 0)//									HIJO 2 -> 2nd cmd
		{
			dup2(p.tub[0], 0);
			dup2(p.outfile, 1);
			p.path = ft_find_path(argv[3], envp);
			p.split_cmd = ft_split(argv[3], ' ');
			execve(p.path, p.split_cmd, envp);
			free(p.path);
			free(p.split_cmd);
		}
		close(p.outfile);
	}
	waitpid(p.id_hijo_1, NULL, 0);
	waitpid(p.id_hijo_2, NULL, 0);
	close_all();
	return (0);
}