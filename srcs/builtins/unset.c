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

static void	env_pop_list(t_env **env)
{
	t_env	*cur;
	t_env	*next;

	cur = *env;
	next = cur ->next;
	free(cur->value);
	free(cur->key);
	cur->value = next->value;
	cur->key = next->key;
	cur->next = next->next;
	free(next);
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
		prev = env;
		if ((tmp = get_env_var(av[i], env)))
		{
			if (tmp == prev->value)
				env_pop_list(&env);
			else
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
		}
		i++;
	}
	return (0);
}
