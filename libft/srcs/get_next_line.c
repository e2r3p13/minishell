/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 20:00:11 by lfalkau           #+#    #+#             */
/*   Updated: 2019/11/14 00:22:43 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

static t_lf		*gnl_find_or_create_fd(t_lf **lst, int fd)
{
	while (*lst)
	{
		if ((*lst)->fd == fd)
			return (*lst);
		lst = &(*lst)->next;
	}
	if (!(*lst = (t_lf *)malloc(sizeof(t_lf))))
		return (NULL);
	(*lst)->fd = fd;
	(*lst)->next = NULL;
	if (!((*lst)->mem = (char *)malloc(sizeof(char) * BUFFER_SIZE)))
		return (NULL);
	ft_memset((*lst)->mem, 0, BUFFER_SIZE);
	return (*lst);
}

static void		gnl_free_fd(t_lf **lst, int fd)
{
	t_lf *elm;

	if (*lst && (*lst)->fd == fd)
	{
		elm = *lst;
		*lst = (*lst)->next;
		free(elm->mem);
		free(elm);
		return ;
	}
	while (*lst && (*lst)->next)
	{
		if ((*lst)->next->fd == fd)
		{
			elm = ((*lst)->next->next);
			free((*lst)->next->mem);
			free((*lst)->next);
			(*lst)->next = elm;
			return ;
		}
		*lst = (*lst)->next;
	}
}

static int		gnl_is_eol_cpy(char *mem, char *dst)
{
	int	i;
	int j;

	while (*dst)
		dst++;
	i = 0;
	j = 0;
	while (i < BUFFER_SIZE && mem[i] != '\n')
	{
		dst[i] = mem[i];
		i++;
	}
	dst[i] = '\0';
	if (i < BUFFER_SIZE && mem[i++] == '\n')
	{
		while (i < BUFFER_SIZE)
			mem[j++] = mem[i++];
		while (j < BUFFER_SIZE)
			mem[j++] = '\0';
		return (1);
	}
	ft_memset(mem, '\0', BUFFER_SIZE);
	return (0);
}

static int		gnl_read_line(char *mem, int fd, char **line)
{
	int nb_rb;

	while ((nb_rb = read(fd, mem, BUFFER_SIZE)))
	{
		if (nb_rb == -1)
			return (-1);
		if (gnl_is_eol_cpy(mem, *line))
			return (1);
		if (!(*line = ft_realloc(*line)))
		{
			free(line);
			return (-1);
		}
	}
	return (0);
}

int				get_next_line(int fd, char **line)
{
	static t_lf		*lst_fd = NULL;
	t_lf			*elm_fd;
	int				ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	if (!(elm_fd = gnl_find_or_create_fd(&lst_fd, fd)))
		return (-1);
	if (!line || !(*line = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	ft_memset(*line, 0, BUFFER_SIZE + 1);
	if (*(elm_fd->mem))
	{
		if (gnl_is_eol_cpy(elm_fd->mem, *line))
			return (1);
		if (!(*line = ft_realloc(*line)))
		{
			free(line);
			return (-1);
		}
	}
	if (!(ret = gnl_read_line(elm_fd->mem, elm_fd->fd, line)))
		gnl_free_fd(&lst_fd, fd);
	return (ret);
}
