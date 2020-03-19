/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 00:35:57 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/19 14:52:32 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "keys.h"

static void handle_return(t_cmd *cmd)
{
	printf("\nVotre commande: '%s'\n", cmd->raw);
}

static void handle_escape(t_cmd *cmd, char *buf)
{
	if (buf[1] == 91)
	{
		if (buf[2] == ESC_KEY_UP)
			printf("UP KEY\n");
		if (buf[2] == ESC_KEY_DOWN)
			printf("DOWN KEY\n");
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
	if (pop(cmd))
		write(0, "\b \b", ft_strlen("\b \b"));
}

char *get_cmd()
{
	t_cmd			*cmd;
	char			buf[4];

	enable_raw_mode();
	cmd = new_cmd();
	while (1)
	{
		ft_memset(buf, 0, 4);
		read(0, &buf, 4);
		if (buf[0] == ESCAPE_KEY)
			handle_escape(cmd, buf);
		else if (buf[0] == RETURN_KEY)
			handle_return(cmd);
		else if (buf[0] == BACKSPACE_KEY)
			handle_backspace(cmd);
		else
		{
			push(buf[0], cmd);
			write(0, buf, 1);
		}
	}
	return (cmd->raw);
}
