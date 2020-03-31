/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 16:46:03 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/02 10:38:58 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	env_add_back(t_env *head, char *str)
{
	t_env	*cur;
	t_env	*new;

	if (!(new = (t_env *)malloc(sizeof(t_env))))
		return ;
	new->key = ft_strndup(str, ft_strchr(str, '=') - str);
	new->value = ft_strdup(ft_strchr(str, '=') + 1);
	cur = head;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}


int ms_export(int ac, char **av, t_env *env)
{
	t_env	*cur;
	char	*var;
	char	*tmp;
	int	i;

	cur = env;
	i = 0;
	if (ac < 2)
		return (0);
	while (av[i])
	{
		if (ft_strchr(av[i], '='))
		{
			var = ft_strndup(av[i], ft_strchr(av[i], '=') - av[i]);
			if ((tmp = get_env_var(var, env)))
			{
				while (cur->next && cur->value != tmp)
					cur = cur->next;
				cur->value = ft_strdup(ft_strchr(av[i], '=') + 1);
			}
			else
				env_add_back(env, av[i]);
		}
		i++;
	}
	return (0);
}
