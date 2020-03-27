/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 22:27:09 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/27 14:46:21 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Just write the cmd line at the end of the history file, with a newline
void	save_cmd(t_cmd *cmd, t_hst *hst, t_bool pushback)
{
	int	len;
	int	fd;

	if ((fd = open(HISTORY_PATH, O_WRONLY | O_APPEND | O_CREAT, 77777)) != -1)
	{
		len = ft_strlen(cmd->raw);
		if (len > 0)
		{
			write(fd, cmd->raw, ft_strlen(cmd->raw));
			write(fd, "\n", 1);
			if (pushback)
				push_back_hst(&hst, cmd);
		}
		close(fd);
	}
}

void	free_hst(t_hst	*hst)
{
	if (hst)
	{
		while(hst->prev)
		{
			free_cmd(hst->cmd);
			hst = hst->prev;
			free(hst->next);
		}
		free(hst->cmd);
		free(hst);
	}
}

int		push_back_hst(t_hst **hst, t_cmd *cmd)
{
	t_hst	*new;

	if (*hst)
	{
		while ((*hst)->next)
			*hst = (*hst)->next;
		if ((*hst)->cmd->raw[0] == '\0')
		{
			*hst = (*hst)->prev;
			pop_back_hst((*hst)->next);
		}
		if (!(new = malloc(sizeof(t_hst))))
			return (0);
		(*hst)->next = new;
		new->cmd = cmd;
		new->prev = *hst;
		new->next = NULL;
		(*hst) = new;
	}
	else
	{
		if (!(*hst = malloc(sizeof(t_hst))))
			return (0);
		(*hst)->cmd = cmd;
		(*hst)->prev = NULL;
		(*hst)->next = NULL;
	}
	return (1);
}

void	pop_back_hst(t_hst	*hst)
{
	while (hst->next)
		hst = hst->next;
	free_cmd(hst->cmd);
	if (hst->prev)
		hst->prev->next = NULL;
	free(hst);
}

t_hst	*get_hst(void)
{
	char	*raw;
	t_cmd	*cmd;
	t_hst	*hst;
	int		fd;

	hst = NULL;
	if ((fd = open(HISTORY_PATH, O_RDONLY)) != -1)
	{
		while (get_next_line(fd, &raw))
		{
			if (!(cmd = malloc(sizeof(t_cmd))))
				return (NULL);
			cmd->raw = raw;
			cmd->len = ft_strlen(cmd->raw);
			cmd->capacity = cmd->len;
			if (!push_back_hst(&hst, cmd))
			{
				free_hst(hst);
				return (NULL);
			}
		}
		close(fd);
		return (hst);
	}
	return (NULL);
}
