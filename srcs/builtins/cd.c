/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 16:44:15 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/25 12:11:47 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ms_cd(int ac, char **av, char **env)
{
	char *path;

	av[ac] = NULL;
	if ((path = av[1]) == NULL)
		path = get_env_var("HOME=", env);
	if (path == NULL || chdir(path) == -1)
	{
		write(1, "cd: no such file or directory: ", 31);
		write(1, av[1], ft_strlen(av[1]));
		write(1, "\n", 1);
		return (1);
	}
	return (0);
}
