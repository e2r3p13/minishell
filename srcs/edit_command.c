/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 18:31:02 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/20 00:06:12 by lfalkau          ###   ########.fr       */
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

t_bool push(char c, t_cmd *cmd)
{
	if (cmd->len == cmd->capacity)
	{
		if (!stretch(cmd))
			return (false);
	}
	if (cmd->cpos == cmd->len)
		cmd->raw[cmd->len] = c;
	else
		insert_at(c, cmd);
	cmd->len++;
	cmd->cpos++;
	return (true);
}

void remove_at(t_cmd *cmd)
{
	size_t l;

	l = cmd->cpos;
	while (l - 1 < cmd->len)
	{
		cmd->raw[l - 1] = cmd->raw[l];
		l++;
	}
	cmd->raw[l - 1] = 0;
}

t_bool pop(t_cmd *cmd)
{
	if (cmd->len > 0)
	{
		if (cmd->len == cmd->cpos)
		{
			cmd->raw[cmd->len - 1] = 0;
		}
		else
		{
			if (cmd->cpos == 0)
				return (false);
			remove_at(cmd);
		}
		cmd->len--;
		cmd->cpos--;
		return (true);
	}
	return (false);
}

t_bool stretch(t_cmd *cmd)
{
	char	*new_raw;

	cmd->capacity *= 2;
	if (!(new_raw = malloc(sizeof(char) * cmd->capacity)))
		return (false);
	ft_memset(new_raw, 0, cmd->capacity);
	ft_memcpy(new_raw, cmd->raw, cmd->len);
	free(cmd->raw);
	cmd->raw = new_raw;
	return (true);
}

t_bool move_cursor_left(t_cmd *cmd)
{
	if (cmd->cpos > 0)
	{
		cmd->cpos--;
		return (true);
	}
	return (false);
}

t_bool move_cursor_right(t_cmd *cmd)
{
	if (cmd->cpos < cmd->len)
	{
		cmd->cpos++;
		return (true);
	}
	return (false);
}

t_bool join_commands(t_cmd *c1, char *c2)
{
	char	*new_cmd;
	size_t	len;

	pop(c1);
	if (!(new_cmd = ft_strjoin(c1->raw, c2)))
		return (false);
	len = ft_strlen(new_cmd);
	free(c1->raw);
	free(c2);
	c1->raw = new_cmd;
	c1->len = len;
	c1->capacity = len;
	c1->cpos = len;
	return (true);
}
