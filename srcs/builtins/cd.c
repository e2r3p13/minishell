/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 16:44:15 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/24 23:14:53 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static size_t	ft_strlen(char *s)
{
	int l;

	l = 0;
	while (*s++)
		l++;
	return (l);
}

static int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned long i;

	i = 0;
	while (s1[i] && s2[i] && i < n && s1[i] == s2[i])
		i++;
	return (i == n ? 0 : ((unsigned char)s1[i] - (unsigned char)s2[i]));
}

static char		*get_env_var(char *var_name, char **env)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(var_name);
	while (env[i])
	{
		if (ft_strncmp(var_name, env[i], len) == 0)
			return (env[i] + len);
		i++;
	}
	return (NULL);
}

int 			main(int ac, char **av, char **env)
{
	if (ac > 1)
	{
		if (chdir(av[1]) == -1)
		{
			write(1, "cd: no such file or directory: ", 31);
			write(1, av[1], ft_strlen(av[1]));
			write(1, "\n", 1);
			return (1);
		}
		return (0);
	}
	else
	{
		if (chdir(get_env_var("HOME=", env)) == -1)
		{
			write(1, "cd: no home directory\n", 29);
			return (1);
		}
		return (0);
	}
}
