/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_reg_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 20:27:44 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/09 20:53:06 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int	open_reg_file(char *path, int flags, mode_t mode)
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
