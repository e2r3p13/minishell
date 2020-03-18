/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_editing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 18:31:02 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/18 20:28:57 by lfalkau          ###   ########.fr       */
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
	return (cmd);
}

int push(char c, t_cmd *cmd)
{
	if (cmd->len == cmd->capacity)
	{
		if (stretch(cmd) == -1)
			return (-1);
	}
	cmd->raw[cmd->len] = c;
	cmd->len++;
	return (0);
}

void pop(t_cmd *cmd)
{
	if (cmd->len > 0)
	{
		cmd->raw[cmd->len] = 0;
		cmd->len--;
	}
}

int insert(char c, int index, t_cmd *cmd)
{
	int l;

	if (cmd->len == cmd->capacity)
	{
		if (stretch(cmd) == -1)
			return (-1);
	}
	l = cmd->len;
	while (l > index)
	{
		cmd->raw[l] = cmd->raw[l - 1];
		l--;
	}
	cmd->raw[index] = c;
	return (0);
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
