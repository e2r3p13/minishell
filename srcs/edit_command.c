/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 18:31:02 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/19 00:43:06 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *new_cmd()
{
	t_cmd *cmd;

	if (!(cmd = malloc(sizeof(t_cmd))))
		return (NULL);
	if (!(cmd->raw = malloc(sizeof(char) * 32)))
		return (NULL);
	ft_memset(cmd->raw, 0, 32);
	cmd->capacity = 32;
	cmd->len = 0;
	cmd->cpos = 0;
	return (cmd);
}

static void insert_at(char c, t_cmd *cmd)
{
	size_t l;

	l = cmd->len;
	while (l > cmd->cpos)
	{
		cmd->raw[l] = cmd->raw[l - 1];
		l--;
	}
	cmd->raw[cmd->cpos] = c;
}

int push(char c, t_cmd *cmd)
{
	if (cmd->len == cmd->capacity)
	{
		if (stretch(cmd) == -1)
			return (-1);
	}
	if (cmd->cpos == cmd->len)
		cmd->raw[cmd->len] = c;
	else
		insert_at(c, cmd);
	cmd->len++;
	cmd->cpos++;
	return (0);
}

static void remove_at(t_cmd *cmd)
{
	size_t l;

	l = cmd->cpos;
	while (l < cmd->len)
	{
		cmd->raw[l - 1] = cmd->raw[l];
		l++;
	}
}

void pop(t_cmd *cmd)
{
	if (cmd->len > 0)
	{
		if (cmd->len == cmd->cpos)
			cmd->raw[cmd->len - 1] = 0;
		else
			remove_at(cmd);
		cmd->len--;
		cmd->cpos--;
	}
}

int stretch(t_cmd *cmd)
{
	char	*new_raw;

	cmd->capacity *= 2;
	if (!(new_raw = malloc(sizeof(char) * cmd->capacity)))
		return (-1);
	ft_memset(new_raw, 0, cmd->capacity);
	ft_memcpy(new_raw, cmd->raw, cmd->len);
	free(cmd->raw);
	cmd->raw = new_raw;
	return (0);
}
