/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 15:57:51 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/20 15:22:03 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_minishell_pid;
extern int g_current_prompt;

void int_handler(int signal)
{
	if (getpid() == g_current_prompt)
	{
		exit(0);
		write(0, "\n", 1);
	}
	signal = 0;
}

void term_handler(int signal)
{
	if (getpid() == g_minishell_pid)
		exit(0);
	signal = 0;
}
