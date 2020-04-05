/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 12:00:44 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/07 15:37:25 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

// Return the length of a (char **) array
int arglen(char **av)
{
	int i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

int open_reg_file(char *path, int flags, mode_t mode)
{
	int			fd;
	struct stat	st;

	fd = mode ? open(path, flags, mode) : open(path, flags);
	if (fd == -1 || fstat(fd, &st) == -1 || (st.st_mode & S_IFMT) != S_IFREG)
	{
		if (fd != -1)
			close(fd);
		return (-1);
	}
	return (fd);
}

int open_file(char *path, int flags, mode_t mode)
{
	int			fd;
	struct stat	st;

	fd = mode ? open(path, flags, mode) : open(path, flags);
	if (fd == -1 || fstat(fd, &st) == -1 || (st.st_mode & S_IFMT) == S_IFDIR)
	{
		if (fd != -1)
			close(fd);
		return (-1);
	}
	return (fd);
}
