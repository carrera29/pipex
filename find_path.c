/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarre <clcarrer@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:59:05 by clcarre           #+#    #+#             */
/*   Updated: 2022/08/09 10:52:00 by clcarre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_strjoin(char const *s1, char const *s2, char x)
{
	char	*str;
	int		i;
	int		ii;

	if (!s1 || !s2)
		return (0);
	i = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (0);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	if (x)
		str[i++] = x;
	ii = 0;
	while (s2[ii])
		str[i++] = s2[ii++];
	str[i] = '\0';
	free((void *)s1);
	return (str);
}

static char	*ft_split_path(char *cmd, char	*envp)
{
	t_pipex		x;
	static int	i;

	if (!envp || !cmd)
		return (0);
	x.split_path = ft_split(envp, ':');
	if (x.split_path[i++])
		x.path = ft_strjoin(x.split_path[i], cmd, '/');
	if (!x.path)
		return (0);
	free(x.split_path);
	return (x.path);
}

char	*ft_find_path(char *cmd, char *envp[])
{
	t_pipex	x;

	x.i = 0;
	while (envp[x.i++])
	{	
		if (ft_strncmp(envp[x.i], "PATH", 4) == 0)
		{
			x.split_cmd = ft_split(cmd, ' ');
			x.path = ft_split_path(x.split_cmd[0], &envp[x.i][5]);
			while (access(x.path, 0) != 0 && x.path)
			{
				free(x.path);
				x.path = ft_split_path(x.split_cmd[0], &envp[x.i][5]);
			}
			free(x.split_cmd);
			return (x.path);
		}
	}
	return (0);
}

// int	main(int argc, char *argv[], char *env[])
// {
// 	char	*cmd = "ls -l";

// 	printf("El path correcto para '%s' es: %s\n", cmd, ft_find_path(cmd, env));
// 	return (0);
// }