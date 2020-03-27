/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 15:13:41 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/26 20:41:20 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct termios	g_save;
extern int		g_exitcode;

int	main(int ac, char **av, char **env)
{

	av[ac] = NULL;
	g_exitcode = 0;
	tcgetattr(STDIN_FILENO, &g_save);;
	signal(SIGINT, ctrlc_handler);
	return (minishell(env));
}
