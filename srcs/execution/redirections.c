/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 13:25:38 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/28 12:37:59 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

static void	remove_rdr(char **cmd)
{
	int i;

	i = 2;
	while (cmd[i])
	{
		cmd[i - 2] = cmd[i];
		i++;
	}
	cmd[i - 2] = NULL;
}

static int	dgreat_redirection(char **cmd)
{
	int		fd;

	if ((fd = open_file(cmd[1], O_WRONLY | O_CREAT | O_APPEND, 0666)) == -1)
		return (EXIT_FAILURE);
	remove_rdr(cmd);
	dup2(fd, 1);
	return (EXIT_SUCCESS);
}

static int	great_redirection(char **cmd)
{
	int		fd;

	if ((fd = open_file(cmd[1], O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
		return (EXIT_FAILURE);
	remove_rdr(cmd);
	dup2(fd, 1);
	return (EXIT_SUCCESS);
}

static int	less_redirection(char **cmd)
{
	int		fd;

	if ((fd = open_file(cmd[1], O_RDONLY, 0)) == -1)
		return (EXIT_FAILURE);
	remove_rdr(cmd);
	dup2(fd, 0);
	return (EXIT_SUCCESS);
}

int			make_redirections(t_ast *ast)
{
	int		i;
	t_bool	drf;

	i = 0;
	drf = EXIT_SUCCESS;
	while (ast->cmd[i] && drf == EXIT_SUCCESS)
	{
		if (ft_strcmp(ast->cmd[i], ">>") == 0)
			drf |= dgreat_redirection(&ast->cmd[i]);
		else if (ft_strcmp(ast->cmd[i], ">") == 0)
			drf |= great_redirection(&ast->cmd[i]);
		else if (ft_strcmp(ast->cmd[i], "<") == 0)
			drf |= less_redirection(&ast->cmd[i]);
		else
			i++;
	}
	return (drf);
}
