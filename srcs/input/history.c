/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 22:27:09 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/10 20:04:27 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/*
** The t_hst struct is a double linked list that contains all commands of the
** minishell_history at the beginning of the program.
** Note that edit history commands will NOT modify them in the history file.
*/

t_hst	*hst_get(void)
{
	char	*cmd;
	t_hst	*hst;
	int		fd;

	hst = NULL;
	if ((fd = open_reg_file(HISTORY_PATH, O_RDONLY, 0)) != -1)
	{
		while (get_next_line(fd, &cmd))
		{
			if (hst_push(&hst, cmd) == EXIT_FAILURE)
				break ;
		}
		close(fd);
		free(cmd);
		return (hst);
	}
	return (NULL);
}

int		hst_push(t_hst **hst, char *cmd)
{
	t_hst	*new;

	if (*hst)
	{
		while ((*hst)->next)
			*hst = (*hst)->next;
	}
	if (!(new = malloc(sizeof(t_hst))))
		return (EXIT_FAILURE);
	if (*hst)
		(*hst)->next = new;
	new->cmd = cmd;
	new->prev = *hst;
	new->next = NULL;
	(*hst) = new;
	return (EXIT_SUCCESS);
}

void	hst_pop(t_hst **hst)
{
	if (!*hst)
		return ;
	while ((*hst)->next)
		*hst = (*hst)->next;
	free((*hst)->cmd);
	if ((*hst)->prev)
	{
		*hst = (*hst)->prev;
		free((*hst)->next);
		(*hst)->next = NULL;
	}
	else
	{
		free(*hst);
		*hst = NULL;
	}
}

void	hst_free(t_hst *hst)
{
	if (hst)
	{
		while (hst->next)
			hst = hst->next;
		while (hst->prev)
		{
			free(hst->cmd);
			hst = hst->prev;
			free(hst->next);
		}
		free(hst->cmd);
		free(hst);
	}
}

void	hst_print(t_hst *hst)
{
	printf("-----\n");
	if (hst)
	{
		while (hst->next)
			hst = hst->next;
		while (hst)
		{
			printf("%s\n", hst->cmd);
			hst = hst->prev;
		}
	}
	printf("-----\n");
}
