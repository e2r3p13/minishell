/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 15:57:51 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/21 18:59:55 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_pid;

void ctrlc_handler(int signal)
{
	if (getppid() == g_pid)
	{
		write(1, "\n", 1);
		exit(signal);
	}
}

void ctrld_handler(int signal)
{
	exit(signal);
}
