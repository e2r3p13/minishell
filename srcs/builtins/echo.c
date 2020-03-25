/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 16:44:50 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/25 12:29:36 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		set_flag(char *arg, int *f)
{
	arg++;

	while (*arg)
	{
		if (*arg == 'n')
			*f |= 0b1000;
		else
			return (0);
		arg++;
	}
	return (1);
}

int				ms_echo(int ac, char **av)
{
	int		i;
	int		f;

	i = 1;
	f = 0b0000;
	av[ac] = NULL;
	while (i < ac && ft_strncmp(av[i], "-", 1) == 0)
	{
		if (set_flag(av[i], &f))
			i++;
		else
			break;
	}
	while (i < ac)
	{
		write(1, av[i], ft_strlen(av[i]));
		if (i != ac - 1)
			write(1, " ", 1);
		i++;
	}
	if (!(f & 0b1000))
		write(1, "\n", 1);
	return (0);
}
