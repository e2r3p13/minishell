/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 22:27:09 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/20 18:53:50 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_cmd(char *line, char *path)
{
	int	len;
	int	fd;

	if ((fd = open(path, O_WRONLY | O_APPEND | O_CREAT, 77777)))
	{
		len = ft_strlen(line);
		if (len > 0)
		{
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
		}
		close(fd);
	}
}
