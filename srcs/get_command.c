/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 00:35:57 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/19 00:52:35 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "keys.h"

static void handle_return(t_cmd *cmd)
{
	cmd->len++;
	cmd->len--;
}

static void handle_escape_input(t_cmd *cmd)
{
	cmd->len++;
	cmd->len--;
}

static void refresh_line(char **env, t_cmd *cmd)
{
	write(0, "\u001b[{2}K\r", ft_strlen("\u001b[{2}K\r"));
	prompt(env);
	write(0, cmd->raw, ft_strlen(cmd->raw));
}

char *get_cmd(char **env)
{
	t_cmd			*cmd;
	char			c;
	size_t			cpos;

	enable_raw_mode();
	cmd = new_cmd();
	cpos = 0;
	while (1)
	{
		read(0, &c, 1);
		if (c == ESCAPE_KEY)
			handle_escape_input(cmd);
		else if (c == RETURN_KEY)
			handle_return(cmd);
		else if (c == BACKSPACE_KEY)
			pop(cmd);
		else
		{
			push(c, cmd);
			cpos++;
		}
		refresh_line(env, cmd);
	}
	return (cmd->raw);
}
