/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 15:13:41 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/06 13:42:20 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool			g_next = false;
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
	g_exitcode = 0;
	if (!isatty(0))
	{
		write(1, "minishell: pipe input not allowed\n", 34);
		return (EXIT_FAILURE);
	}
	tcgetattr(STDIN_FILENO, &g_save);
	signal(SIGINT, sighandler);
	signal(SIGKILL, sighandler);
	history = hst_get();
	env = env_get(e);
	if (env)
		return (minishell(env, history));
	else
		return (EXIT_FAILURE);
}
