/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bccyv <bccyv@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 12:22:02 by bccyv             #+#    #+#             */
/*   Updated: 2020/04/30 16:59:21 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

extern t_bool	g_should_run;

int	ms_exit(void)
{
	write(1, "exit\n", 5);
	g_should_run = false;
	return (EXIT_SUCCESS);
}
