#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>		// perror() && printf()
#include <stdlib.h>		// malloc()	&& free()
#include <unistd.h>		// access() && close() && pipe() && fork() && dup2() && waitpid()
#include <sys/wait.h>	// open()
#include <fcntl.h>		// file control options

typedef struct	s_pipex
{
	int		i;
	int		pipe_1_[2];
	int		pipe_2_[2];
	int		infile;
	int		outfile;
	int		status;
	pid_t	id_child_1;
	pid_t	id_child_2;
	char	*path;
	char	**split_path;
	char	**split_cmd;
}	t_pipex;

// FIND PATH
char				*ft_find_path(char *cmd, char *env[]);

// SPLIT
char				**ft_split(char const *s, char c);

// UTILS
size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

#endif