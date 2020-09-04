/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:37:37 by lfalkau           #+#    #+#             */
/*   Updated: 2020/09/04 18:49:41 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "keys.h"
#include <stdlib.h>

/*
** Here's minishell, far from a real shell, but close of our hearts
** It can be run as interactive or not.
** minishell first waits for input, then lexes it into a token list, in order
** to check the grammar first.
** Once it have be done, for each incoming command, minishell transform the
** token list into an execution tree (parser job) and execute it.
** Runs until EOI is reached (ctrl-D).
*/

int				g_exitcode = 0;
t_bool			g_should_run = true;

int		minishell(t_env *env, t_hst **hst, t_bool it)
{
	char		*cmd;

	while (g_should_run)
	{
		it ? prompt(env) : 1;
		if (!(cmd = it ? get_it_cmd(hst) : get_cmd()))
			continue ;
		if (*cmd == EOI)
			break ;
		if (ft_strlen(cmd) == 0)
			hst_pop(hst);
		else
			minishell_core(cmd, env);
		it ? 1 : free(cmd);
	}
	return (g_exitcode);
}

void	minishell_core(char *cmd, t_env *env)
{
	t_lxr	**lxrlst;
	t_ast	*ast;
	int		i;

	if ((lxrlst = lxr_split(lexer(cmd))))
	{
		i = 0;
		while (lxrlst[i] && expand(lxrlst[i], env) == EXIT_SUCCESS)
		{
			if ((ast = ast_create(lxrlst[i])))
			{
				g_exitcode = execute(ast, env);
				ast_free(ast);
			}
			lxr_free(lxrlst[i]);
			i++;
		}
		free(lxrlst);
	}
}
