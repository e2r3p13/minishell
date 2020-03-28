/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 09:55:01 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/28 23:12:47 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// The t_cms structure is a dynamic array, including a 'char * raw' that wrap
// the command itself, a 'size_t len' that contains the cmd length,
// a 'size_t capacity' that indicates how many bytes have been allocated,
// that is also the max length cmd can be and a 'size_t pos' showing us
// the cursor position is the raw, vefry useful for command editing.

// Insert a character at the cursor position
t_bool	cmd_push_char(char c, t_cmd *cmd)
{
	size_t len;

	if (!cmd)
		return (false);
	len = cmd->len;
	if (!ft_isprint(c) || (len == cmd->capacity && !cmd_stretch(cmd)))
		return (false);
	while (len > cmd->pos)
	{
		cmd->raw[len] = cmd->raw[len - 1];
		len--;
	}
	cmd->raw[cmd->pos] = c;
	cmd->len++;
	cmd->pos++;
	return (true);
}

// Remove a character at the cursor position
t_bool	cmd_pop_char(t_cmd *cmd)
{
	size_t pos;

	if (!cmd)
		return (false);
	pos = cmd->pos;
	if (cmd->len > 0 && pos > 0)
	{
		while (pos - 1 < cmd->len)
		{
			cmd->raw[pos - 1] = cmd->raw[pos];
			pos++;
		}
		cmd->raw[pos - 1] = 0;
		cmd->len--;
		cmd->pos--;
		return (true);
	}
	return (false);
}

// Try to move the cursor in the struct and return weither it succeeds or not
t_bool	cmd_can_move_cursor(t_cmd *cmd, t_dir dir)
{
	if (!cmd)
		return (false);
	if (dir == left && cmd->pos > 0)
	{
		cmd->pos--;
		return (true);
	}
	else if (dir == right && cmd->pos < cmd->len)
	{
		cmd->pos++;
		return (true);
	}
	return (false);
}

// Append history file with the command's raw
void	cmd_save(t_cmd *cmd)
{
	int	fd;

	if ((fd = open(HISTORY_PATH, O_WRONLY | O_APPEND | O_CREAT, 77777)) != -1)
	{
		if (cmd && cmd->raw && ft_strlen(cmd->raw) > 0)
		{
			write(fd, cmd->raw, ft_strlen(cmd->raw));
			write(fd, "\n", 1);
		}
		close(fd);
	}
}
