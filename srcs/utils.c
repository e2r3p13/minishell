/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 12:00:44 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/02 10:38:14 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Return the content of a given environment variable name
// The given variable name must be trailed by '='
char	*get_env_var(char *var_name, char **env)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(var_name);
	while (env[i])
	{
		if (ft_strncmp(var_name, env[i], len) == 0)
			return (env[i] + len);
		i++;
	}
	return (NULL);
}

// Return the length of a (char **) array
int arglen(char **av)
{
	int i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}
