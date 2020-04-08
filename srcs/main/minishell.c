/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:37:37 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/08 13:53:12 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "keys.h"
#include "tokens.h"

int	minishell(t_env *env, t_hst *hst)
{
	t_cmd	*cmd;
	t_lxr	**lexlst;
	int		i;

	while (true)
	{
		cmd = cmd_get(env, &hst);
		if (cmd && cmd->raw && ft_strlen(cmd->raw) &&
			(lexlst = lxr_split(lexer(cmd->raw))))
		{
			i = 0;
			while (lexlst[i] && expand(lexlst[i], env))
			{
				tree_exec(parser(lexlst[i]), env);
				lxr_free(lexlst[i++]);
			}
			free(lexlst);
		}
		else if (cmd)
			hst_pop_cmd(&hst);
	}
	return (0);
}
