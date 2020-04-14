/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 21:37:36 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/14 11:03:53 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"
#include <stdio.h>

void	ast_print(t_ast *ast)
{
	if (!ast || ast->token == 0)
		return ;
	if (ast->token != CMD)
	{
		printf("token: %i\n", ast->token);
		ast_print(ast->left);
		ast_print(ast->right);
	}
	else
		printf("%s\n", *(ast->cmd));
}
