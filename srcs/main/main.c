/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 15:13:41 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/08 13:52:53 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	main(int ac, char **av, char **e)
{
	t_hst	*history;
	t_env	*env;

	av[ac] = NULL;
	if (!isatty(0))
	{
		write(1, "minishell: pipe input not allowed\n", 34);
		return (EXIT_FAILURE);
	}
	tcgetattr(STDIN_FILENO, &g_save);
	signal(SIGINT, sighandler);
	signal(SIGKILL, sighandler);
	history = hst_get();
	if ((env = env_get(e)))
		return (minishell(env, history));
	else
		return (EXIT_FAILURE);
}
