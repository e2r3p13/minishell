/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   great_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 20:15:35 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/16 22:01:56 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int			great_redirection(t_ast *ast, t_env *env)
{
	int		fd[2];
	char	*file_name;

	file_name = *(ast->right->cmd);
	fd[0] = open_reg_file(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd[0] < 0)
		return (EXIT_FAILURE);
	fd[1] = dup(STDOUT_FILENO);
	close(STDOUT_FILENO);
	dup2(fd[0], STDOUT_FILENO);
	execute(ast->left, env);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	return (EXIT_SUCCESS);
}
