/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:37:37 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/13 21:38:27 by lfalkau          ###   ########.fr       */
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

int	minishell(t_env *env, t_hst **hst, t_bool it)
{
	char	*cmd;
	t_lxr	**lexlst;
	t_ast	*ast;
	int		i;

	while (true)
	{
		it ? prompt(env) : 1;
		if (!(cmd = it ? get_it_cmd(hst) : get_cmd()))
			continue ;
		if (*cmd == EOI || ft_strcmp(cmd, "exit") == 0)
			break ;
		if (ft_strlen(cmd) == 0)
			hst_pop(hst);
		else if ((lexlst = lxr_split(lexer(cmd))))
		{
			i = 0;
			while (lexlst[i] && expand(lexlst[i], env) == EXIT_SUCCESS)
			{
				if ((ast = ast_create(lexlst[i])))
					ast_print(ast);
				lxr_free(lexlst[i++]);
			}
			free(lexlst);
		}
	}
	return (0);
}
