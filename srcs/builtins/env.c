/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 16:46:32 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/25 12:26:37 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ms_env(int ac, char **av, char **env)
{
	int i;

	i = 0;
	av[ac] = NULL;
	while (env[i])
	{
		write(1, env[1], ft_strlen(env[i]));
		write(1, "\n", 1);
	}
	return (0);
}
