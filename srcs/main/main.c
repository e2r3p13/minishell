/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 15:13:41 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/02 10:18:17 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				g_chpid = 0;
struct termios	g_save;
int				g_exitcode = 0;
char			*g_execve_av[2] = {GDD_PATH, NULL};
void			*g_ascii_tokens[256] =
{
	['<'] = lxr_redirect,
	['>'] = lxr_redirect,
	['|'] = lxr_redirect,
	['$'] = lxr_variable,
	[';'] = lxr_newline,
	['\n'] = lxr_newline,
	['\''] = lxr_quote,
	['\"'] = lxr_quote,
};

int	main(int ac, char **av, char **env)
{
	t_hst	*history;

	av[ac] = NULL;
	g_exitcode = 0;
	tcgetattr(STDIN_FILENO, &g_save);
	signal(SIGINT, ctrlc_handler);
	history = hst_get();
	return (minishell(env, history));
}
