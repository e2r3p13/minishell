/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 00:35:57 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/19 11:21:09 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "keys.h"

static void handle_return(t_cmd *cmd)
{
	printf("RETURN\n");
	cmd->len++;
	cmd->len--;
}

static void handle_escape_input(t_cmd *cmd, char *buf)
{
	if (buf[1] == 91)
	{
		if (buf[2] == ESC_KEY_UP)
			printf("UP KEY\n");
		if (buf[2] == ESC_KEY_DOWN)
			printf("DOWN KEY\n");
		if (buf[2] == ESC_KEY_RIGHT)
			printf("RIGHT KEY\n");
		if (buf[2] == ESC_KEY_LEFT)
			printf("LEFT KEY\n");
	}
	else
	{
		printf("ESC KEY\n");
	}
	cmd->len++;
	cmd->len--;
}

char *get_cmd()
{
	t_cmd			*cmd;
	size_t			cpos;
	char			buf[4];

	enable_raw_mode();
	cmd = new_cmd();
	cpos = 0;
	while (1)
	{
		ft_memset(buf, 0, 4);
		read(0, &buf, 4);
		if (buf[0] == ESCAPE_KEY)
			handle_escape_input(cmd, buf);
		else if (buf[0] == RETURN_KEY)
			handle_return(cmd);
		else if (buf[0] == BACKSPACE_KEY)
			pop(cmd);
		else
		{
			push(buf[0], cmd);
			write(0, buf, 1);
			cpos++;
		}
	}
	return (cmd->raw);
}
