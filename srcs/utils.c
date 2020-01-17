/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 12:00:44 by lfalkau           #+#    #+#             */
/*   Updated: 2020/01/17 12:03:03 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
