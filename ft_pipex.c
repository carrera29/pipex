/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarre <clcarrer@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:22:42 by clcarre           #+#    #+#             */
/*   Updated: 2022/06/20 14:49:12 by clcarre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int execve(const char *path, char *const argv[], char *envp[]);
// dirección path del comando, comando a ejecutar, 

int	ft_find_path(int envp)
{
	
}

int	main(int argc, char **argv)
{
	int		tub[2];
	int		fd1;
	int		fd2;
	pid_t	id;
	char	*path;

	if (pipe(tub) == -1)
		return (0);
	id = fork();
	if (id < 0)
		return (0);
	else if (id == 0)// HIJO
	{
		close(fd[0]);// cerramos el lado de lectura
		fd1 = open(argv[1], O_RDONLY);
		path = ft_find_path(char *envp);
		if (fd1 == -1)
			return (0);
		close(fd[1]);
	}
	else// PADRE
	{
		close(fd[1]);//cerramos el lado de escritura
		fd2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 777);
		if (read(fd[0], &fd2, sizeof(char)) == -1)
			return (0);
		close(fd[0]);
		printf("El proceso hijo dice: %s", s);
	}
	return (0);
}
