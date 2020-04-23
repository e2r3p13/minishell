/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 21:37:36 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/23 16:55:27 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"
#include <stdlib.h>

#include <stdio.h>

t_ast	*ast_new(void)
{
	t_ast	*ast;

	if (!(ast = malloc(sizeof(t_ast))))
		return (NULL);
	ast->token = 0;
	ast->cmd = NULL;
	ast->left = NULL;
	ast->right = NULL;
	return (ast);
}

int		lxr_cmdsize(t_lxr *lxr)
{
	int size;

	size = 0;
	while (lxr && lxr->token != PIPE)
	{
		size++;
		lxr = lxr->next;
	}
	return (size);
}

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
