/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 13:55:58 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/16 12:29:54 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"
#include <stdlib.h>

void	*g_redirection_functions[6] =
{
	[0] = NULL,
	[CMD] = &execute_command,
	[PIPE] = &pipe_redirection,
	[GREAT] = &great_redirection,
	[DGREAT] = &dgreat_redirection,
	[LESS] = &less_redirection,
};

int	execute(t_ast *ast, t_env *env)
{
	int	(*exef)(t_ast *ast, t_env *env);

	if ((exef = g_redirection_functions[ast->token]))
		return (exef(ast, env));
	else
		return (EXIT_FAILURE);
}
