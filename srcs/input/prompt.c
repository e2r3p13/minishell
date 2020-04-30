/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:38:04 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/30 15:05:13 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

extern int	g_exitcode;
char		*g_execve_av[2] = {SCRIPT_PATH, NULL};

/*
** Switched from old prompt with path / git informations to minimalist prompt
*/

void		prompt(void)
{
	if (g_exitcode == EXIT_SUCCESS)
		write(1, "\033[1;92mminishell$ \033[0;00m", 25);
	else
		write(1, "\033[1;91mminishell$ \033[0;00m", 25);
}
