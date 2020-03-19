/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 18:31:02 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/21 14:12:15 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *new_cmd()
{
	t_cmd *cmd;

	if (!(cmd = malloc(sizeof(t_cmd))))
		return (NULL);
	if (!(cmd->raw = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (NULL);
	ft_memset(cmd->raw, 0, BUFFER_SIZE + 1);
	cmd->capacity = BUFFER_SIZE;
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

t_bool stretch(t_cmd *cmd)
{
	char	*new_raw;

	cmd->capacity *= 2;
	if (!(new_raw = malloc(sizeof(char) * (cmd->capacity + 1))))
		return (false);
	ft_memset(new_raw, 0, cmd->capacity + 1);
	ft_memcpy(new_raw, cmd->raw, cmd->len);
	free(cmd->raw);
	cmd->raw = new_raw;
	return (true);
}

t_bool can_move_cursor_left(t_cmd *cmd)
{
	if (cmd->cpos > 0)
	{
		cmd->cpos--;
		return (true);
	}
	return (false);
}

t_bool can_move_cursor_right(t_cmd *cmd)
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

void erase(t_cmd *cmd)
{
	ft_memset(cmd->raw, 0, cmd->capacity);
	cmd->len = 0;
	cmd->cpos = 0;
}
