/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_command_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 09:55:01 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/26 10:13:07 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// The t_cms structure is a dynamic array, including a 'char * raw' that wrap
// the command itself, a 'size_t len' that contains the cmd length,
// a 'size_t capacity' that indicates how many bytes have been allocated,
// that is also the max length cmd can be and a 'size_t cpos' showing us
// the cursor position is the raw, vefry useful for command editing.

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

// Insert a character at the cursor position
t_bool push(char c, t_cmd *cmd)
{
	if (!ft_isprint(c) || (cmd->len == cmd->capacity && !stretch(cmd)))
		return (false);
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

// Remove a character at the cursor position
t_bool pop(t_cmd *cmd)
{
	if (cmd->len > 0)
	{
		if (cmd->len == cmd->cpos)
			cmd->raw[cmd->len - 1] = 0;
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

// Try to move the cursor in the struct and return weither it succeeds or not
t_bool can_move_cursor(t_cmd *cmd, t_dir dir)
{
	if (dir == left && cmd->cpos > 0)
	{
		cmd->cpos--;
		return (true);
	}
	else if (dir == right && cmd->cpos < cmd->len)
	{
		cmd->cpos++;
		return (true);
	}
	return (false);
}
