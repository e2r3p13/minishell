/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 22:27:09 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/07 15:26:01 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// The t_hst struct is a double linked list that contains all commands of the
// minishell_history at the beginning of the program.
// Note that edit history commands will NOT modify them in the history file.

// Get the whole minishell's command history from HISTORY_PATH
// And turns it into a double linked list
t_hst	*hst_get(void)
{
	char	*raw;
	t_cmd	*cmd;
	t_hst	*hst;
	int		fd;

	hst = NULL;
	if ((fd = open_reg_file(HISTORY_PATH, O_RDONLY, 0)) != -1)
	{
		while (get_next_line(fd, &raw))
		{
			if (!(cmd = malloc(sizeof(t_cmd))))
				return (NULL);
			cmd->raw = raw;
			cmd->len = ft_strlen(cmd->raw);
			cmd->capacity = cmd->len;
			if (!hst_push_cmd(&hst, cmd))
				return (hst_free(hst));
		}
		close(fd);
		free(raw);
		return (hst);
	}
	return (NULL);
}

// Push a given t_cmd at the end of the history list
t_bool	hst_push_cmd(t_hst **hst, t_cmd *cmd)
{
	t_hst	*new;

	if (!cmd)
		return (failure);
	if (*hst)
	{
		while ((*hst)->next)
			*hst = (*hst)->next;
		if (!(new = malloc(sizeof(t_hst))))
			return ((t_bool)cmd_free(cmd));
		(*hst)->next = new;
		new->cmd = cmd;
		new->prev = *hst;
		new->next = NULL;
		(*hst) = new;
	}
	else
	{
		if (!(*hst = malloc(sizeof(t_hst))))
			return ((t_bool)cmd_free(cmd));
		(*hst)->cmd = cmd;
		(*hst)->prev = NULL;
		(*hst)->next = NULL;
	}
	return (success);
}

// Remove the last element of the history list
void	hst_pop_cmd(t_hst **hst)
{
	if (*hst)
	{
		while ((*hst)->next)
			*hst = (*hst)->next;
		cmd_free((*hst)->cmd);
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
}

// Replace the last command of the history list by a given command
t_bool	hst_reuse_cmd(t_hst **hst, t_cmd *cmd)
{
	if (!(*hst) || !cmd)
		return (failure);
	while ((*hst)->next)
		*hst = (*hst)->next;
	free((*hst)->cmd->raw);
	if (!((*hst)->cmd->raw = ft_strdup(cmd->raw)))
		return (failure);
	(*hst)->cmd->len = cmd->len;
	(*hst)->cmd->capacity = (*hst)->cmd->len;
	(*hst)->cmd->pos = (*hst)->cmd->len;
	return (success);
}

// Free the whole history list
void	*hst_free(t_hst *hst)
{
	if (hst)
	{
		while (hst->next)
			hst = hst->next;
		while(hst->prev)
		{
			cmd_free(hst->cmd);
			hst = hst->prev;
			free(hst->next);
		}
		free(hst->cmd);
		free(hst);
	}
	return (NULL);
}
