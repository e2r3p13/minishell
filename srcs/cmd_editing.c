/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_editing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 18:31:02 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/18 19:06:00 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *new_cmd()
{
	t_cmd cmd;

	if !(cmd.raw = malloc(sizeof(char) * 32))
		return (NULL);
	ft_memset(cmd.raw, 0, 32);
	cmd.capacity = 32;
	cmd.len = 0;
	return (&cmd);
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
	if (len > 0)
	{
		cmd->raw[cmd->len] = 0;
		cmd->len--;
	}
}

int insert(int index, t_cmd *cmd)
{
	if (cmd->len == cmd->capacity)
	{
		if (stretch(cmd) == -1)
			return (-1);
	}

}

int stretch(t_cmd *cmd)
{

}
