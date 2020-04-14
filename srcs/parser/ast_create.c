/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:56:33 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/14 11:12:56 by lfalkau          ###   ########.fr       */
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
	ast->token = 0;
	ast->cmd = NULL;
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

static t_ast	*ast_create_leaf_node(t_lxr **lxr)
{
	int		i;
	t_ast	*new;

	if (!(new = malloc(sizeof(t_ast))))
		return (NULL);
	if (!(new->cmd = malloc(sizeof(char *) * (lxr_cmdsize(*lxr) + 1))))
	{
		free(new);
		return (NULL);
	}
	i = 0;
	while (*lxr && (*lxr)->token == WORD)
	{
		new->cmd[i] = (*lxr)->raw;
		*lxr = (*lxr)->next;
		i++;
	}
	new->token = CMD;
	return (new);
}

static t_ast	*ast_create_branch_node(t_ast *ast, t_lxr **lxr)
{
	t_ast	*new;

	if (!(new = ast_new()))
		return (NULL);
	new->left = ast;
	new->token = ast_get_token(lxr);
	new->right = ast_create_leaf_node(lxr);
	return (new);
}

t_ast		*ast_create(t_lxr *lxr)
{
	t_ast	*ast;

	ast = ast_create_leaf_node(&lxr);
	while (lxr && lxr->token == REDIRECT)
	{
		ast = ast_create_branch_node(ast, &lxr);
	}
	return (ast);
}
