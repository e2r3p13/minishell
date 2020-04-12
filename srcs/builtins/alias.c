/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 14:16:24 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/12 17:24:37 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_als	*g_als;

int	ms_alias(int ac, char **av)
{
	if ((av[1] && ft_strcmp(av[1], "minishell") == 0) || !g_als)
		return (1);
	return (ms_export(ac, av, g_als));
}
