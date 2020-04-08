/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 16:46:14 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/08 20:40:25 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int	ms_unset(int ac, char **av, t_env *env)
{
	t_env	*tmp;
	int		i;

	i = 0;
	av[ac] = NULL;
	while (av[++i])
	{
		tmp = env;
		if (ft_strcmp(av[i], "_") && get_env_var(av[i], env))
		{
			while (ft_strcmp(tmp->key, av[i]) != 0)
				tmp = tmp->next;
			if (tmp == env)
				env_remove_first(env);
			else
				env_remove_elm(env, tmp);
		}
	}
	return (EXIT_SUCCESS);
}
