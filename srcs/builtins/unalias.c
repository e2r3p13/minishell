/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unalias.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 14:19:13 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/12 14:34:28 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_als	*g_als;

int	ms_unalias(int ac, char **av)
{
	if ((av[1] && ft_strcmp(av[1], "minishell") == 0) || !g_als)
		return (1);
	return (ms_unset(ac, av, g_als));
}
