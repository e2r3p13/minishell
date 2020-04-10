/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:37:37 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/10 10:18:51 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "keys.h"
#include "tokens.h"

int	minishell(t_env *env, t_bool it)
{
	char	*cmd;
	t_lxr	**lexlst;
	int		i;

	while (true)
	{
		prompt(env);
		if (!(cmd = it ? get_it_cmd() : get_cmd()) || !ft_strlen(cmd))
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
