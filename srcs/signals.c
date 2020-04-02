/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 15:57:51 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/02 10:21:49 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_chpid;
extern int	g_exitcode;

void sighandler(int signal)
{
	signal = 130;
	if (getpid() == g_chpid)
		exit(signal);
}
