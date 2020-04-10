/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 14:55:27 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/10 14:59:54 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_var(char *var_name, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(var_name, env->key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int		env_size(t_env *env)
{
	int i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

void	*env_free(t_env *env)
{
	t_env *tmp;

	while (env)
	{
		tmp = env;
		free(tmp->key);
		free(tmp->value);
		env = env->next;
		free(tmp);
	}
	return (NULL);
}
