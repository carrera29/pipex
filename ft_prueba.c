#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	int	fd[2];
	int	id;
	int	x;
	int n1;
	int n2;
	int i;
	int r;
		// tub[0] -> READ 	-> el padre
		// tub[1] -> WRITE -> el hijo

	if (pipe(fd) == -1)
		return (0);
	id = fork();
	if (id == -1)
		return (0);
	else if (id == 0)// HIJO
	{
		if (pipe(fd[0]) == -1)
			return (0);
		id = fork();
		if (id == 0)
		{
			close(fd[0]);// cerramos el lado de lectura
			printf("Ingrese el número a multiplicar \n");
			scanf("%d", &n1);
			if (write(fd[1], &n1, sizeof(int)) == -1)
				return (0);
			close(fd[1]);
		}
		else
		{
			close(fd[0]);// cerramos el lado de lectura	
			printf("Ingrese el otro número a multiplicar \n");
			scanf("%d", &n2);
			if (write(fd[1], &n2, sizeof(int)) == -1)
				return (0);
			close(fd[1]);
		}
	}
	else// PADRE
	{
		close(fd[1]);// cerramos el lado de escritura
		if (read(fd[0], &n1, sizeof(int)) == -1)
			return (0);
		if (read(fd[0], &n2, sizeof(int)) == -1)
			return (0);
		r = n1 * n2;
			printf("%d * %d = %d\n", n1, n2, r);
		close(fd[0]);
		wait(NULL);
	}
	return (0);
}
/*int	main(int argc, char **argv)
{
	int	fd[2];
	int	id;
	int	x;
	int	y;
	int	c;

	if (pipe(fd) == -1)
		return (0);
	id = fork();
	if (id == 0)// HIJO
	{
		close(fd[0]);// Cerramos el lado del lectura
		printf("Escriba el numero a multipicar...");
		scanf("%d", &x);
		write(fd[1], &x, sizeof(int));
		close(fd[1]);// Cerramos la comunicación
	}
	else// PADRE
	{
		close(fd[1]);// Cerramos el lado del escritura
		y = 0;
		read(fd[0], &c, sizeof(int));
		while (y++ >= 10)
			printf("%d x %d = %d\n", c, y, (c*y));
		close (fd[0]);
	}
	return (0);
}*/
