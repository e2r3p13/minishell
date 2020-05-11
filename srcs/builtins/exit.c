/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bccyv <bccyv@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 12:22:02 by bccyv             #+#    #+#             */
/*   Updated: 2020/05/11 13:18:21 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

extern t_bool	g_should_run;

static t_bool	ft_isnumber(char *str)
{
	if (*str && (ft_isdigit(*str) || *str == '+' || *str == '-'))
		return (ft_isstrdigit(++str));
	return (*str ? false : true);
}

int				ms_exit(int ac, char **av)
{
	write(1, "exit\n", 5);
	g_should_run = false;
	if (ac == 1)
		return (EXIT_SUCCESS);
	else if (ac == 2)
	{
		if (ft_isnumber(av[1]))
			return (ft_atoi(av[1]));
		else
		{
			write(1, "exit: numeric argument required\n", 32);
			return (255);
		}
	}
	else
	{
		if (ft_isnumber(av[1]))
			write(1, "exit: too many arguments\n", 25);
		else
			write(1, "exit: numeric argument required\n", 32);
		g_should_run = ft_isnumber(av[1]);
		return (ft_isnumber(av[1]) ? EXIT_FAILURE : 255);
	}
}
