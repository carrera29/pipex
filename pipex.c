/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarre <clcarrer@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 15:09:42 by clcarre           #+#    #+#             */
/*   Updated: 2022/08/09 10:59:09 by clcarre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(t_pipex p, char *cmd, char *envp[])
{
	if (!cmd || !envp)
		perror("something is missing");
	if (p.i == 0)
	{
		close(p.pipe[0]);
		dup2(p.infile, 0);
		dup2(p.pipe[1], 1);
		close(p.pipe[1]);
	}
	else
	{
		dup2(p.pipe[0], 0);
		dup2(p.outfile, 1);
	}
	execve(ft_find_path(cmd, envp), ft_split(cmd, ' '), envp);
}

void	ft_pipex(t_pipex p, char **argv, char **envp)
{
	p.i = 0;
	if (p.id_child_1 == 0)
		child_process(p, argv[2], envp);
	else
	{
		close(p.pipe[1]);
		p.i++;
		p.id_child_2 = fork();
		if (p.id_child_2 < 0)
			perror ("fork(2) error");
		else if (p.id_child_2 == 0)
			child_process(p, argv[3], envp);
		close(p.pipe[0]);
	}
	waitpid(p.id_child_1, NULL, 0);
	waitpid(p.id_child_2, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;

	if (argc == 5)
	{
		p.infile = open(argv[1], O_RDONLY);
		p.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_WRONLY, 0644);
		if (p.infile < 0 || p.outfile < 0)
		{	
			write(1, "file error\n", 11);
			return (0);
		}
		if (pipe(p.pipe) == -1)
			perror ("pipe() error");
		p.id_child_1 = fork();
		if (p.id_child_1 == -1)
			perror ("fork(1) error");
		ft_pipex(p, argv, envp);
		close(p.infile);
		close(p.outfile);
	}
	else
		perror("error number of arguments");
	return (0);
}
