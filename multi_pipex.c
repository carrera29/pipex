#include <stdio.h>		// perror() && printf()
#include <stdlib.h>		// malloc()	&& free()
#include <unistd.h>		// access() && close() && pipe() && fork() && dup2() && waitpid()
#include <sys/wait.h>	// open()
#include <fcntl.h>	

int	main(int argc, char **argv, char **envp)
{
	int	pipe1[2];//		child 	->	parent
	int pipe2[2];//		parent	->	child
	int	id_hijo_1;
	int	id_hijo_2;
	int	i;

	if (pipe(pipe1) == -1)
		perror("error pipe(1)");
	if (pipe(pipe2) == -1)
		perror("error pipe(1)");
	id_hijo_1 = fork();
	if (id_hijo_1 < 0)
		perror("error fork(1)");
	i = 0;
	if (id_hijo_1 == 0)
	{
		int	x;
		int	y;

		close(pipe1[0]);
		close(pipe2[1]);
		printf("Escribe el numero a multiplicar\n");
		scanf("%d", &x);
		write(pipe1[1], &x, sizeof(int));
		read(pipe2[0], &y, sizeof(int)) > 0);
		close(pipe1[1]);
		close(pipe2[0]);	
	}
	else
	{
		close(pipe1[1]);
		close(pipe2[0]);
		id_hijo_2 = fork();
		if (id_hijo_2 == -1)
			perror("error fork(1)");
		else if (id_hijo_2 == 0)
		{
			int	z;
			int	w;

			read(pipe1[0], &z, sizeof(int));
			printf("Escribe el otro numero a multiplicar\n");
			scanf("%d", &w);
			z = z * w;
			write(pipe2[1], &z, sizeof(int));
		}
		close(pipe1[0]);
		close(pipe2[1]);
		wait(NULL);
	};
	return(0);
}
