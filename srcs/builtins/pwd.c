/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 16:45:43 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/05 13:01:58 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ms_pwd(int ac, char **av, t_env *env)
{
	av[ac] = NULL;
	if (get_env_var("PWD", env))
	{
		write(1, get_env_var("PWD", env), ft_strlen(get_env_var("PWD", env)));
		write(1, "\n", 1);
		return (EXIT_SUCCESS);
	}
	else
	{
		write(1, "pwd: PWD env variable not found\n", 32);
		return (EXIT_FAILURE);
	}
}
