/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 16:44:50 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/10 17:41:28 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

static int		is_flag(char *s)
{
	if (!*s)
		return (false);
	while (*s)
		if (!ft_isinset("n", *s++))
			return (false);
	return (true);
}

static void		set_flag(char *arg, int *f)
{
	arg++;
	while (*arg)
	{
		if (*arg == 'n')
			*f |= 0b1000;
		arg++;
	}
}

int				ms_echo(int ac, char **av)
{
	int		i;
	int		f;

	i = 1;
	f = 0b0000;
	av[ac] = NULL;
	while (i < ac && *av[i] == '-' && is_flag(av[i] + 1))
		set_flag(av[i++], &f);
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
