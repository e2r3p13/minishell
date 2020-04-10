/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 23:03:24 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/11 00:11:48 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>

void	hst_remove_elm(t_hst **hst, t_hst *elm)
{
	hst = NULL;
	elm = NULL;
}

void	hst_replace_last(t_hst **hst)
{
	hst = NULL;
}

void	hst_save(char *cmd)
{
	int fd;

	fd = open_reg_file(HISTORY_PATH, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd != -1)
	{
		write(fd, cmd, ft_strlen(cmd));
		write(fd, "\n", 1);
		close(fd);
	}
}
