/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 14:55:27 by lfalkau           #+#    #+#             */
/*   Updated: 2020/05/14 13:52:09 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

char		*get_env_var(char *var_name, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(var_name, env->key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int			env_size(t_env *env)
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

void		*env_free(t_env *env)
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

static int	set_underscore_var(t_env *env, char **av)
{
	char	*tmp;
	char	*cwd;

	if (!(env->key = ft_strdup("_")))
	{
		free(env);
		return (EXIT_FAILURE);
	}
	if ((cwd = getcwd(NULL, 0)))
	{
		if ((tmp = ft_strcjoin(cwd, av[0], '/')))
			env->value = tmp;
		else
		{
			free(cwd);
			return (EXIT_FAILURE);
		}
		free(cwd);
	}
	env->next = NULL;
	return (EXIT_SUCCESS);
}

t_env		*env_from_scratch(char **av)
{
	t_env	*env;
	char	*tmp;
	char	*cwd;

	if (!(env = malloc(sizeof(t_env))))
		return (NULL);
	if (set_underscore_var(env, av) == EXIT_FAILURE)
		return (NULL);
	make_assignment(env, "SHLVL=1");
	if ((cwd = getcwd(NULL, 0)))
	{
		if ((tmp = ft_strcjoin("PWD", cwd, '=')))
		{
			make_assignment(env, tmp);
			free(tmp);
		}
		free(cwd);
	}
	return (env);
}
