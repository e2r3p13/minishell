/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 13:55:58 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/23 17:00:21 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"
#include <stdlib.h>
#include <unistd.h>

static void	reset_shell(int fd[2])
{
	dup2(fd[0], 0);
	dup2(fd[1], 1);
}

int			execute(t_ast *ast, t_env *env)
{
	int status;
	int	fd[2];

	if (ast->token == PIPE)
	{
		return (pipeline(ast, env));
	}
	else
	{
		fd[0] = dup(0);
		fd[1] = dup(1);
		if (ast->token == CMD_R && make_redirections(ast) == EXIT_FAILURE)
		{
			reset_shell(fd);
			write(1, "minishell: Invalid redirection\n", 31);
			return (EXIT_FAILURE);
		}
		status = execute_command(ast, env);
		reset_shell(fd);
		return (status);
	}
}
