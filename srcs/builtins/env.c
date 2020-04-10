/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 16:46:32 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/10 17:42:49 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int	ms_env(int ac, char **av, t_env *env)
{
	av[ac] = NULL;
	while (env)
	{
		write(1, env->key, ft_strlen(env->key));
		write(1, "=", 1);
		write(1, env->value, ft_strlen(env->value));
		write(1, "\n", 1);
		env = env->next;
	}
	return (0);
}
