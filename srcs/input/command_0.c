/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 00:35:57 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/28 23:07:59 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "keys.h"

// Read and process stdin, return a t_cmd, pushed at the end of history
t_cmd	*cmd_get(t_hst **hst)
{
	char	buf[5];

	if (!(hst_push_cmd(hst, cmd_new())))
		return (NULL);
	while (true)
	{
		ft_memset(buf, 0, 5);
		read(0, &buf, 4);
		if (*buf == ESCAPE_KEY)
			cmd_handle_arrows(hst, buf + 1);
		else if (*buf == RETURN_KEY)
			break;
		else if (*buf == BACKSPACE_KEY)
			cmd_handle_backspace((*hst)->cmd);
		else if (*buf == CTRL_D_KEY && cmd_handle_ctrld((*hst)->cmd))
			break;
		else if (*buf == CTRL_U_KEY)
			cmd_handle_ctrlu((*hst)->cmd);
		else
			cmd_handle_character((*hst)->cmd, buf);
	}
	return (cmd_handle_return(*hst));
}

// Bash style Ctrl-D, exit shell if empty command, DEL's behaviour otherwise
t_bool	cmd_handle_ctrld(t_cmd *cmd)
{
	if (cmd->len == 0)
	{
		if (cmd->capacity < 5 && !cmd_stretch(cmd))
			return (false);
		ft_memcpy(cmd->raw, "exit\0", 5);
		write(1, "exit", 4);
		return (true);
	}
	if (cmd->pos < cmd->len)
	{
		write(1, CURSOR_RIGHT, 3);
		cmd->pos++;
		cmd_handle_backspace(cmd);
	}
	return (false);
}

// Bash style Ctrl-U should erase the command
void	cmd_handle_ctrlu(t_cmd *cmd)
{
	term_move_cursor(left, cmd->pos);
	term_writen(' ', cmd->len);
	term_move_cursor(left, cmd->len);
	cmd_erase(cmd);
}
