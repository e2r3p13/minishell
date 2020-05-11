/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bccyv <bccyv@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 12:22:02 by bccyv             #+#    #+#             */
/*   Updated: 2020/05/11 11:40:48 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

extern t_bool	g_should_run;

int	ms_exit(int ac, char **av)
{
	write(1, "exit\n", 5);
	g_should_run = false;
	if (ac == 1)
		return (EXIT_SUCCESS);
	else if (ac == 2)
	{
		if (ft_isstrdigit(av[1]))
			return (ft_atoi(av[1]));
		else
		{
			write(1, "minishell: exit only takes an unic numeric value\n", 49);
			return (255);
		}
	}
	else
	{
		write(1, "minishell: exit only takes an unic numeric value\n", 49);
		g_should_run = ft_isstrdigit(av[1]);
		return (ft_isstrdigit(av[1]) ? EXIT_FAILURE : 255);
	}
}
