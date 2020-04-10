/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:37:37 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/10 17:20:11 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "keys.h"
#include "tokens.h"

/*
** Here's minishell, far from a real shell, but close of our hearts
** It can be run as interactive or not.
** minishell first waits for input, then lexes it into a token list, in order
** to check the grammar first.
** Once it have be done, for each incoming command, minishell transform the
** token list into an execution tree (parser job) and execute it.
** Runs until EOI is reached (ctrl-D).
*/

int	minishell(t_env *env, t_hst *hst, t_bool it)
{
	char	*cmd;
	t_lxr	**lexlst;
	int		i;

	hst = NULL;
	while (true)
	{
		if (it)
			prompt(env);
		if (!(cmd = it ? get_it_cmd() : get_cmd()))
			continue ;
		if (*cmd == EOI || ft_strcmp(cmd, "exit") == 0)
			break ;
		if ((lexlst = lxr_split(lexer(cmd))))
		{
			i = 0;
			while (lexlst[i] && expand(lexlst[i], env) == EXIT_SUCCESS)
			{
				tree_exec(parser(lexlst[i]), env);
				lxr_free(lexlst[i++]);
			}
			free(lexlst);
		}
	}
	return (0);
}
