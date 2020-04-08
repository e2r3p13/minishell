/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/28 22:46:43 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/08 20:29:12 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "keys.h"

static void	cmd_move_cursor(t_hst *hst, char key)
{
	if (key == KEY_RIGHT)
		if (cmd_can_move_cursor(hst->cmd, right))
			write(1, CURSOR_RIGHT, 3);
	if (key == KEY_LEFT)
		if (cmd_can_move_cursor(hst->cmd, left))
			write(1, CURSOR_LEFT, 3);
}

static void	cmd_scroll_history(t_hst **hst, char key)
{
	size_t	len;
	size_t	pos;

	len = (*hst)->cmd->len;
	pos = (*hst)->cmd->pos;
	*hst = key == KEY_UP ? (*hst)->prev : (*hst)->next;
	term_move_cursor(left, pos);
	term_writen(' ', len);
	term_move_cursor(left, len);
	write(1, (*hst)->cmd->raw, (*hst)->cmd->len);
	(*hst)->cmd->pos = (*hst)->cmd->len;
}

void		cmd_esc_seq(t_hst **hst, char *buf)
{
	if (*buf == KEY_LEFT || *buf == KEY_RIGHT)
		cmd_move_cursor(*hst, *buf);
	if ((*buf == KEY_UP && (*hst)->prev) || (*buf == KEY_DOWN && (*hst)->next))
		cmd_scroll_history(hst, *buf);
}

void		cmd_handle_backspace(t_cmd *cmd)
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
