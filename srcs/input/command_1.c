/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/28 22:46:43 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/28 22:59:33 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "keys.h"

// Handle cursor movement, and history commands
void	cmd_handle_arrows(t_hst **hst, char *buf)
{
	size_t	len;
	size_t	pos;

	if (*buf++ == '[')
	{
		if (*buf == ESC_KEY_RIGHT)
			if (cmd_can_move_cursor((*hst)->cmd, right))
				write(1, CURSOR_RIGHT, 3);
		if (*buf == ESC_KEY_LEFT)
			if (cmd_can_move_cursor((*hst)->cmd, left))
				write(1, CURSOR_LEFT, 3);
		if ((*buf == ESC_KEY_UP && (*hst)->prev) ||
			(*buf == ESC_KEY_DOWN && (*hst)->next))
		{
			len = (*hst)->cmd->len;
			pos = (*hst)->cmd->pos;
			*hst = *buf == ESC_KEY_UP ? (*hst)->prev : (*hst)->next;
			term_move_cursor(left, pos);
			term_writen(' ', len);
			term_move_cursor(left, len);
			write(1,(*hst)->cmd->raw, (*hst)->cmd->len);
			(*hst)->cmd->pos = (*hst)->cmd->len;
		}
	}
}

// Can either return the command or start the multiline command process
t_cmd	*cmd_handle_return(t_hst *hst)
{
	if (hst->next)
		hst_reuse_cmd(&hst, hst->cmd);
	cmd_save(hst->cmd);
	return (hst->cmd);
}

// Delete the character just before the cursor, if there's some
void	cmd_handle_backspace(t_cmd *cmd)
{
	int pos_diff;

	if (cmd_pop_char(cmd))
	{
		write(1, CURSOR_LEFT, 3);
		write(1, cmd->raw + cmd->pos, cmd->len - cmd->pos + 1);
		write(1, " ", 1);
		pos_diff = cmd->len - cmd->pos + 1;
		term_move_cursor(left, pos_diff);
	}
}

// Handle all printable characters, adding them at the good position in the cmd
void	cmd_handle_character(t_cmd *cmd, char *buf)
{
	int		pos_diff;

	while (ft_isprint(*buf) && cmd_push_char(*buf, cmd))
	{
		write(1, buf, 1);
		write(1, cmd->raw + cmd->pos, cmd->len - cmd->pos + 1);
		pos_diff = cmd->len - cmd->pos;
		term_move_cursor(left, pos_diff);
		buf++;
	}
}
