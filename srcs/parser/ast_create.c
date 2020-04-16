/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:56:33 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/16 12:35:13 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"
#include <stdlib.h>

static t_ast	*ast_create_leaf_node(t_lxr **lxr)
{
	int		i;
	t_ast	*new;

	if (!(new = malloc(sizeof(t_ast))))
		return (NULL);
	i = lxr_cmdsize(*lxr);
	if (!(new->cmd = malloc(sizeof(char *) * (i + 1))))
	{
		free(new);
		return (NULL);
	}
	new->cmd[i] = NULL;
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
