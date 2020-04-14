/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 13:55:58 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/14 20:17:19 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"

void	*g_redirection_functions[6] =
{
	[0] = NULL,
	[CMD] = &execute_command,
	[PIPE] = &pipe_redirection,
	[GREAT] = &great_redirection,
	[DGREAT] = &dgreat_redirection,
	[LESS] = &less_redirection,
};

int	exectute(t_ast *ast, t_env *env)
{
	int	(*exef)(t_ast *ast, t_env *env);

	exef = g_redirection_functions[ast->token];
	return (exef(ast, env));
}

int execute_command(t_ast *ast, t_env *env)
{
	
}
