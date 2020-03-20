/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 00:35:57 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/20 18:59:13 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "keys.h"

static void cmd_return(t_cmd *cmd)
{
	char *next_line;

	//Multiline, if line is trailed by '\'
	if (cmd->raw[cmd->len - 1] == '\\')
	{
		write(1, "\n\033[0;36m» \033[0;00m", 18);
		next_line = get_cmd();
		join_commands(cmd, next_line);
	}
}

static void cmd_escape(t_cmd *cmd, char *buf)
{
	//Handle arrows
	if (buf[1] == '[')
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

static void cmd_backspace(t_cmd *cmd)
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

static void cmd_ctrld(t_cmd *cmd)
{
	if (cmd->len == 0)
	{
		exit(0);
	}
	if (cmd->cpos < cmd->len)
	{
		write(0, "\033[C", ft_strlen("\033[C"));
		cmd->cpos++;
		cmd_backspace(cmd);
	}
}

static void	cmd_character(t_cmd *cmd, char c)
{
	int cpos_diff;

	if (push(c, cmd))
	{
		write(0, &c, 1);
		write(0, cmd->raw + cmd->cpos, cmd->len - cmd->cpos + 1);
		cpos_diff = cmd->len - cmd->cpos;
		for(int i = 0; i < cpos_diff; i++)
			write(0, "\033[D", ft_strlen("\033[D"));
	}
}

char		*get_cmd()
{
	t_cmd	*cmd;
	char	buf[4];

	cmd = new_cmd();
	while (true)
	{
		ft_memset(buf, 0, 4);
		read(0, &buf, 4);
		if (buf[0] == ESCAPE_KEY)
			cmd_escape(cmd, buf);
		else if (buf[0] == RETURN_KEY)
		{
			cmd_return(cmd);
			break;
		}
		else if (buf[0] == BACKSPACE_KEY)
			cmd_backspace(cmd);
		else if (buf[0] == CTRL_D_KEY)
			cmd_ctrld(cmd);
		else
			cmd_character(cmd, buf[0]);
	}
	return (cmd->raw);
}
