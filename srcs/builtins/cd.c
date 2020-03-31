/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 16:44:15 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/31 18:39:51 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ms_cd(int ac, char **av, char **env)
{
	char	*path;
	t_bool	is_allocated;

	av[ac] = NULL;
	is_allocated = false;
	if ((path = av[1]) == NULL)
		path = get_env_var("HOME=", env);
	if (*path == '~')
		if ((path = ft_strjoin(get_env_var("HOME=", env), path + 1)))
			is_allocated = true;
	if (path == NULL || chdir(path) == -1)
	{
		write(1, "cd: no such file or directory: ", 31);
		write(1, av[1], ft_strlen(av[1]));
		write(1, "\n", 1);
		return (1);
	}
	if (path && is_allocated)
		free(path);
	return (0);
}
