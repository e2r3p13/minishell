/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 00:35:57 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/20 21:00:26 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"
#include "keys.h"

static void cmd_return(t_cmd *cmd)
{
	char *next_line;

	//Multiline, if line is trailed by '\'
	if (cmd->raw[cmd->len - 1] == '\\')
	{
		write(1, NEW_LINE_PROMPT, 18);
		next_line = get_cmd();
		join_commands(cmd, next_line);
	}
}

static void cmd_arrows(t_cmd *cmd, char *buf)
{
	//Handle arrows for cmd editing and history
	if (*buf++ == '[')
	{
		if (*buf == ESC_KEY_UP)
			printf("");
		if (*buf == ESC_KEY_DOWN)
			printf("");
		if (*buf == ESC_KEY_RIGHT)
			if (move_cursor_right(cmd))
				write(0, CURSOR_RIGHT, 3);
		if (*buf == ESC_KEY_LEFT)
			if (move_cursor_left(cmd))
				write(0, CURSOR_LEFT, 3);
	}
}

static void cmd_backspace(t_cmd *cmd)
{
	int cpos_diff;

	if (pop(cmd))
	{
		write(0, CURSOR_LEFT, 3);
		write(0, cmd->raw + cmd->cpos, cmd->len - cmd->cpos + 1);
		write(0, " ", 1);
		cpos_diff = cmd->len - cmd->cpos + 1;
		for(int i = 0; i < cpos_diff; i++)
			write(0, CURSOR_LEFT, 3);
	}
}

static void	cmd_character(t_cmd *cmd, char *buf)
{
	int		cpos_diff;

	while (ft_isprint(*buf))
	{
		if (push(*buf, cmd))
		{
			write(0, buf, 1);
			write(0, cmd->raw + cmd->cpos, cmd->len - cmd->cpos + 1);
			cpos_diff = cmd->len - cmd->cpos;
			for(int i = 0; i < cpos_diff; i++)
				write(0, CURSOR_LEFT, 3);
		}
		buf++;
	}
}

static void cmd_ctrld(t_cmd *cmd)
{
	if (cmd->len == 0)
	{
		//Must exit full program;
		exit(0);
	}
	if (cmd->cpos < cmd->len)
	{
		write(0, CURSOR_RIGHT, 3);
		cmd->cpos++;
		cmd_backspace(cmd);
	}
}

char		*get_cmd()
{
	t_cmd	*cmd;
	char	buf[5];

	cmd = new_cmd();
	while (true)
	{
		ft_memset(buf, 0, 5);
		read(0, &buf, 4);
		if (*buf == ESCAPE_KEY)
			cmd_arrows(cmd, buf + 1);
		else if (*buf == RETURN_KEY)
		{
			cmd_return(cmd);
			break;
		}
		else if (*buf == BACKSPACE_KEY)
			cmd_backspace(cmd);
		else if (*buf == CTRL_D_KEY)
			cmd_ctrld(cmd);
		else
			cmd_character(cmd, buf);
	}
	return (cmd->raw);
}
