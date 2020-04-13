/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:56:33 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/13 21:42:38 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"
#include <stdlib.h>

static t_ast	*ast_new(void)
{
	t_ast	*ast;

	if (!(ast = malloc(sizeof(t_ast))))
		return (NULL);
	ast->next = NULL;
	ast->left = NULL;
	ast->right = NULL;
	return (ast);
}

static int	ast_get_token(t_lxr **lxr)
{
	t_lxr	*tmp;

	tmp = *lxr;
	*lxr = (*lxr)->next;
	if (tmp->raw[0] == '|')
		return (PIPE);
	else if (tmp->raw[0] == '<')
		return (LESS);
	else if (tmp->raw[1] == '>')
		return (DGREAT);
	else
		return (GREAT);
}

static int	lxr_cmdsize(t_lxr *lxr)
{
	int size;

	size = 0;
	while (lxr && lxr->token == WORD)
	{
		size++;
		lxr = lxr->next;
	}
	return (size);
}

static t_ast	*ast_create_leaf_node(t_ast *ast, t_lxr **lxr)
{
	int	i;

	if (!(ast->cmd = malloc(sizeof(char *) * (lxr_cmdsize(*lxr) + 1))))
		return (NULL);
	i = 0;
	while (*lxr && (*lxr)->token == WORD)
	{
		ast->cmd[i] = (*lxr)->raw;
		*lxr = (*lxr)->next;
		i++;
	}
	return (EXIT_SUCCESS);
}

static t_ast	*ast_create_branch_node(t_ast **ast, t_lxr **lxr)
{
	t_ast	*new;

	if (!(new = ast_new()))
		return (EXIT_FAILURE);
	new->left = *ast;
	new->token = ast_get_token(lxr);
	new->right = ast_create_leaf_node(*ast, lxr);
	*ast = new;
	return (EXIT_SUCCESS);
}

t_ast		*ast_create(t_lxr *lxr)
{
	t_ast	*ast;

	if (!(ast = ast_new()))
		return (NULL);
	while (lxr)
	{
		if (lxr->token == WORD)
			ast_create_leaf_node(ast, &lxr);
		else
			ast_create_branch_node(&ast, &lxr);
	}
	return (ast);
}
