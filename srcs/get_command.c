/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 00:35:57 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/20 17:42:11 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "keys.h"

extern int g_minishell_pid;

static void handle_return(t_cmd *cmd)
{
	char *next_line;

	save_cmd(cmd->raw, HISTORY_PATH);
	if (cmd->raw[cmd->len - 1] == '\\')
	{
		write(1, "\n»» ", 4);
		next_line = get_cmd();
		join_commands(cmd, next_line);
	}
}

static void handle_escape(t_cmd *cmd, char *buf)
{
	if (buf[1] == 91)
	{
		if (buf[2] == ESC_KEY_UP)
			printf("");
		if (buf[2] == ESC_KEY_DOWN)
			printf("");
		if (buf[2] == ESC_KEY_RIGHT)
		{
			if (move_cursor_right(cmd))
				write(0, "\033[C", ft_strlen("\033[C"));
		}
		if (buf[2] == ESC_KEY_LEFT)
		{
			if (move_cursor_left(cmd))
				write(0, "\033[D", ft_strlen("\033[D"));
		}
	}
	else
	{
		printf("ESC KEY\n");
	}
	cmd->len++;
	cmd->len--;
}

static void handle_backspace(t_cmd *cmd)
{
	int cpos_diff;

	if (pop(cmd))
	{
		write(0, "\033[D", ft_strlen("\033[D"));
		write(0, cmd->raw + cmd->cpos, cmd->len - cmd->cpos + 1);
		write(0, " ", 1);
		cpos_diff = cmd->len - cmd->cpos + 1;
		for(int i = 0; i < cpos_diff; i++)
			write(0, "\033[D", ft_strlen("\033[D"));
	}
}

static void handle_ctrl_d(t_cmd *cmd)
{
	if (cmd->len == 0)
	{
		kill(g_minishell_pid, SIGTERM);
	}
	if (cmd->cpos < cmd->len)
	{
		write(0, "\033[C", ft_strlen("\033[C"));
		cmd->cpos++;
		handle_backspace(cmd);
	}
}

char *get_cmd()
{
	t_cmd			*cmd;
	char			buf[4];

	cmd = new_cmd();
	while (1)
	{
		ft_memset(buf, 0, 4);
		read(0, &buf, 4);
		if (buf[0] == ESCAPE_KEY)
			handle_escape(cmd, buf);
		else if (buf[0] == RETURN_KEY)
		{
			handle_return(cmd);
			break;
		}
		else if (buf[0] == BACKSPACE_KEY)
			handle_backspace(cmd);
		else if (buf[0] == CTRL_D_KEY)
			handle_ctrl_d(cmd);
		else
		{
			push(buf[0], cmd);
			write(0, buf, 1);
		}
	}
	return (cmd->raw);
}
