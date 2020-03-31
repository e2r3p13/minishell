/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 16:46:14 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/25 12:12:16 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	env_pop_list(t_env **env)
{
	t_env	*cur;
	t_env	*next;

	printf("in pop\n");
	cur = *env;
	next = cur ->next;
	free(cur->value);
	free(cur->key);
	cur->value = next->value;
	cur->key = next->key;
	cur->next = next->next;
	free(next);
	printf("end pop\n");
}

int ms_unset(int ac, char **av, t_env *env)
{
	t_env	*cur;
	t_env	*prev;
	char	*tmp;
	int	i;

	i = 1;
	if (ac < 2)
		return (1);
	while (av[i])
	{
		printf("begin, key = %s\t%s\n", env->key, av[i]);
		prev = env;
		if (!(ft_strcmp(get_env_var(prev->key, env), av[i])))
			env_pop_list(&env);
		else if ((tmp = get_env_var(av[i], env)))
		{
			cur = prev;
			while (cur->next && cur->value != tmp)
				cur = cur->next;
			while (prev->next != cur)
				prev = prev->next;
			prev->next = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
		}
		printf("end\n");
		i++;
	}
	return (0);
}
