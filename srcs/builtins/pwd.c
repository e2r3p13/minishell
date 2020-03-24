/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btn_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 16:45:43 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/24 18:41:31 by lfalkau          ###   ########.fr       */
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

static char	*get_env_var(char *var_name, char **env)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(var_name);
	while (env[i])
	{
		if (ft_strncmp(var_name, env[i], len) == 0)
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

int 		main(int ac, char **av, char **env)
{
	av[ac] = NULL;
	write(1, get_env_var("PWD=", env), ft_strlen(get_env_var("PWD=", env)));
	write(1, "\n", 1);
	return (0);
}
