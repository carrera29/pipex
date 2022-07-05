#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>

typedef struct	s_pipex
{
	int		i;
	int		tub[2];
	int		infile;
	int		outfile;
	int		status;
	pid_t	id_hijo_1;
	pid_t	id_hijo_2;
	char	*path;
	char	**split_path;
	char	**split_cmd;
}	t_pipex;

// FIND PATH
char				*ft_find_path(char *cmd, char *env[]);
char				*ft_split_path(char *cmd, char	*env);
char				*ft_strjoin(char const *s1, char const *s2, char x);

// SPLIT
char				**ft_split(char const *s, char c);
// static char			**ft_str(char **split, char const *s, char c);
// static char			*ft_write(char *split, const char *s, int count, int i);
// static unsigned int	ft_division(char const *s, char c);
// void					free_split(char **s);

// UTILS
size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

#endif