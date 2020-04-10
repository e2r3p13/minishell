/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tweak.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 20:45:30 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/10 17:40:39 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void		redi_err(t_psr *head, int fd, int std, char *file)
{
	if (std == 0)
		dup2(fd, STDIN_FILENO);
	else if (std == 1)
		dup2(fd, STDOUT_FILENO);
	close(fd);
	ft_putstr("minishell: ");
	if (file)
		ft_putstr(file);
	else
		ft_putstr("(null)");
	ft_putstr(": No such file or directory\n");
	tree_free(head);
}

static void	tweak_great(t_psr *cur, t_env *env)
{
	char	**name;
	int		fd[2];

	name = (char**)cur->right;
	if ((fd[0] = open(name[0], O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
		return ;
	if (sizeof(cur->left) == sizeof(cur))
		tweak_tree_exec(cur->left, env);
	else
		execute(cur->left, env);
	close(fd[0]);
}

static void	tweak_dgreat(t_psr *cur, t_env *env)
{
	char	**name;
	int		fd[2];
	int		i;
	char	c;

	i = 1;
	name = (char**)cur->right;
	if ((fd[0] = open_file(name[0], O_RDWR | O_CREAT, 0644)) < 0)
		return ;
	while (i > 0)
		i = read(fd[0], &c, 1);
	if (sizeof(cur->left) == sizeof(cur))
		tweak_tree_exec(cur->left, env);
	else
		execute(cur->left, env);
	close(fd[0]);
}

void		tree_free(t_psr *cur)
{
	if (cur->type == 0)
		free(cur->left);
	free(cur->right);
	free(cur);
}

void		tweak_tree_exec(t_psr *cur, t_env *env)
{
	if (cur->type == GREAT)
		tweak_great(cur, env);
	else if (cur->type == DGREAT)
		tweak_dgreat(cur, env);
	else if (cur->type == LESS)
		redirect_less(cur, env);
	else if (cur->type == PIPE)
		redirect_pipe(cur, env);
	else
		execute(cur->left, env);
	tree_free(cur);
}
