/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 15:13:41 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/24 23:29:57 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct termios g_save;

int	main(int ac, char **av, char **env)
{
	av[ac] = NULL;
	tcgetattr(STDIN_FILENO, &g_save);;
	signal(SIGINT, ctrlc_handler);
	enable_raw_mode();
	return (minishell(env));
}
