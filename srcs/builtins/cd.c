/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 16:44:15 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/10 17:41:06 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

static char	*set_path_with_home(char *arg, t_env *env, t_bool *allocated)
{
	char	*home;
	char	*tmp;

	if (!(home = get_env_var("HOME", env)))
		return (NULL);
	if (!arg)
		return (home);
	else
	{
		if ((tmp = ft_strjoin(home, arg + 1)))
		{
			*allocated = true;
			return (tmp);
		}
		return (NULL);
	}
}

int			ms_cd(int ac, char **av, t_env *env)
{
	char	*path;
	t_bool	allocated;

	av[ac] = NULL;
	allocated = false;
	if (!(path = av[1]) || *path == '~')
		path = set_path_with_home(av[1], env, &allocated);
	if (path && chdir(path) == -1)
	{
		write(1, "cd: no such file or directory: ", 31);
		write(1, av[1], ft_strlen(av[1]));
		write(1, "\n", 1);
		return (EXIT_FAILURE);
	}
	else if (!path)
	{
		write(1, "cd: HOME env variable not found\n", 32);
		return (EXIT_FAILURE);
	}
	if (path && allocated)
		free(path);
	return (EXIT_SUCCESS);
}
