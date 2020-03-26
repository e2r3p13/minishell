/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 16:46:42 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/26 11:54:45 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern struct termios g_save;

int ms_exit(int ac, char **av, char **env)
{
	if (av != env)
		av[ac] = NULL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_save);
	exit(0);
}
