#include <unistd.h>
#include <stdio.h>

// int execve(const char *path, char *const argv[], char *envp[]);


int	main(void)
{
	char cmd_PATH[] = "/bin/ls";
	char *argv[] = {"ls -la", NULL};
	char *envp[] = {NULL};

	if (execve(cmd_PATH, argv, envp) == -1)
		printf("Ha fallado\n");
	return (0);
}
