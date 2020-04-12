/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 16:46:03 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/12 14:15:32 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

t_bool			is_valid_assignment(char *s)
{
	int i;

	i = 0;
	while (ft_isalnum(s[i]) || s[i] == '_')
		i++;
	if (s[i] != '=' || i == 0)
	{
		write(1, "export: bad assignment: ", 24);
		write(1, s, ft_strlen(s));
		write(1, "\n", 1);
		return (false);
	}
	return (true);
}

static int		make_assignment(t_env *env, char *a)
{
	t_env	*tmp;
	char	*key;
	char	*val;
	char	*tmp_val;

	if (!(key = ft_strndup(a, ft_strchr(a, '=') - a)))
		return (EXIT_FAILURE);
	if (!(val = ft_strdup(ft_strchr(a, '=') + 1)))
		return (EXIT_FAILURE);
	if ((tmp_val = get_env_var(key, env)))
	{
		tmp = env;
		while (tmp->value != tmp_val)
			tmp = tmp->next;
		free(tmp->value);
		tmp->value = val;
		free(key);
	}
	else
	{
		if (!(env_push_back(env, key, val)))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int				ms_export(int ac, char **av, t_env *env)
{
	int	i;
	int	r_val;

	av[ac] = NULL;
	i = 0;
	r_val = EXIT_SUCCESS;
	while (av[++i])
	{
		if (ft_strncmp(av[i], "_=", 2))
		{
			if (is_valid_assignment(av[i]))
				r_val |= make_assignment(env, av[i]);
			else
				r_val = EXIT_FAILURE;
		}
	}
	return (r_val);
}
