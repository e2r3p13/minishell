/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:37:37 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/29 20:38:50 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "keys.h"
#include "tokens.h"

struct termios	g_ogterm;

int	minishell(char **env, t_hst *history)
{
	t_cmd	*command;
	t_lxr	**lexlst;
	int		i;

	while (true)
	{
		command = cmd_get(env, &history);
		if (command && (lexlst = lxr_split(lexer(command->raw))))
		{
			i = 0;
			while (lexlst[i] && expand(lexlst[i], env))
			{
				tree_exec(parser(lexlst[i]), env);
				lxr_free(lexlst[i++]);
			}
			// Free all things funtion instead of three following lines
			free(lexlst);
			if (ft_strlen(command->raw) == 0)
				hst_pop_cmd(&history);
		}
	}
	return (0);
}
