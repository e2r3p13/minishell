/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 15:16:22 by lfalkau           #+#    #+#             */
/*   Updated: 2020/05/11 15:10:17 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

t_env	*env_get(char **e)
{
	t_env	*env;
	t_env	*t;
	int		i;
	char	*l;

	i = 0;
	env = NULL;
	while (e[i])
	{
		if (!(t = malloc(sizeof(t_env))))
			return (env_free(env));
		t->next = env;
		env = t;
		t->value = ft_strdup(ft_strchr(e[i], '=') + 1);
		t->key = ft_strndup(e[i], ft_strlen(e[i]) - ft_strlen(t->value) - 1);
		if (!ft_strcmp(t->key, "SHLVL") && (l = ft_itoa(ft_atoi(t->value) + 1)))
		{
			free(t->value);
			t->value = l;
		}
		i++;
	}
	return (env);
}

char	**env_to_arr(t_env *e)
{
	int		i;
	int		j;
	char	**array;
	char	*str;

	i = env_size(e);
	if (!(array = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	array[i] = NULL;
	j = 0;
	while (j < i)
	{
		if (!(str = ft_strcjoin(e->key, e->value, '=')))
		{
			array[j] = NULL;
			return (array);
		}
		array[j] = str;
		e = e->next;
		j++;
	}
	return (array);
}

int		env_push_back(t_env *env, char *key, char *value)
{
	t_env	*new;

	if (!(new = (t_env *)malloc(sizeof(t_env))))
	{
		free(key);
		free(value);
		return (EXIT_FAILURE);
	}
	new->key = key;
	new->value = value;
	while (env && env->next)
		env = env->next;
	env->next = new;
	new->next = NULL;
	return (EXIT_SUCCESS);
}

void	env_remove_first(t_env *env)
{
	t_env	*tmp;

	free(env->key);
	free(env->value);
	if ((tmp = env->next))
	{
		env->key = tmp->key;
		env->value = tmp->value;
		env->next = tmp->next;
		free(tmp);
	}
}

void	env_remove_elm(t_env *env, t_env *elm)
{
	t_env	*tmp;

	while (env->next != elm)
		env = env->next;
	tmp = elm->next;
	free(elm->key);
	free(elm->value);
	free(elm);
	env->next = tmp;
}
