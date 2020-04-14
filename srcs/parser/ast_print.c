/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 21:37:36 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/14 11:15:42 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"
#include <stdio.h>

void	ast_print(t_ast *ast, int depth)
{
	if (!ast || ast->token == 0)
		return ;
	if (ast->token != CMD)
	{
		printf("depth: %d, token: %i\n", depth, ast->token);
		ast_print(ast->left, depth + 1);
		ast_print(ast->right, depth + 1);
	}
	else
		printf("depth: %d, cmd: %s\n", depth, *(ast->cmd));
}
