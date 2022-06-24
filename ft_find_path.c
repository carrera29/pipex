/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarre <clcarrer@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:15:17 by clcarre           #+#    #+#             */
/*   Updated: 2022/06/24 13:09:43 by clcarre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "ft_split.c"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		ii;

	if (!s1)
		return (0);
	i = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (0);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	ii = 0;
	while (s2[ii])
		str[i++] = s2[ii++];
	str[i] = '\0';
	free((void *)s1);
	return (str);
}

char	*ft_split_path(char	*env, char *cmd)
{
	static int	i;
	char		**s;
	char		*path;

	s = ft_split(env, ':');
	path = ft_strjoin(s[i], cmd);
	if (!path)
		return (0);
	i++;
	return (path);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s1[i] == s2[i] && i < ((unsigned int)n - 1))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_find_path(char *env[], char *cmd)
{
	int	i;

	i = 0;
	while (env[i])
	{	
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			while (execve(ft_split_path(&env[i][5], cmd), &cmd, env) == -1)
			// int execve(const char *path, char *const cmd[], char *env[]);
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[], char *env[])
{
	char	*cmd = "ls -la";

	printf("El path es: %s\n", ft_find_path(env, cmd));
	return (0);
}
