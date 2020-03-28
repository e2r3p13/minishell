/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 00:35:57 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/28 20:33:39 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"
#include "keys.h"

// static void	print_hst(t_hst *hst)
// {
// 	while(hst)
// 	{
// 		printf("\n%s", hst->cmd->raw);
// 		hst = hst->prev;
// 	}
// 	printf("\n");
// }

// Can either return the command or start the multiline command process
char	*cmd_return(t_hst *hst)
{
	if (hst->next)
		use_old_cmd(&hst, hst->cmd);
	save_cmd(hst->cmd);
	return (hst->cmd->raw);
}

// Delete the character just before the cursor, if there's some
void	cmd_backspace(t_cmd *cmd)
{
	int cpos_diff;

	if (pop(cmd))
	{
		write(1, CURSOR_LEFT, 3);
		write(1, cmd->raw + cmd->cpos, cmd->len - cmd->cpos + 1);
		write(1, " ", 1);
		cpos_diff = cmd->len - cmd->cpos + 1;
		move_cursor(left, cpos_diff);
	}
}

// Handle all printable characters, adding them at the good position in the cmd
void	cmd_character(t_cmd *cmd, char *buf)
{
	int		cpos_diff;

	while (ft_isprint(*buf) && push(*buf, cmd))
	{
		write(1, buf, 1);
		write(1, cmd->raw + cmd->cpos, cmd->len - cmd->cpos + 1);
		cpos_diff = cmd->len - cmd->cpos;
		move_cursor(left, cpos_diff);
		buf++;
	}
}

// Bash style Ctrl-D, exit shell if empty command, DEL's behaviour otherwise
t_bool	cmd_ctrld_shoould_exit(t_cmd *cmd)
{
	if (cmd->len == 0)
	{
		if (cmd->capacity < 5 && !stretch(cmd))
			return (false);
		ft_memcpy(cmd->raw, "exit\0", 5);
		write(1, "exit", 4);
		return (true);
	}
	if (cmd->cpos < cmd->len)
	{
		write(1, CURSOR_RIGHT, 3);
		cmd->cpos++;
		cmd_backspace(cmd);
	}
	return (false);
}

// Ctrl-U should erase the command
void	cmd_ctrlu(t_cmd *cmd)
{
	move_cursor(left, cmd->cpos);
	fill_with(' ', cmd->len);
	move_cursor(left, cmd->len);
	erase(cmd);
}

// Handle cursor movement, and history commands
void	cmd_arrows(t_hst **hst, char *buf)
{
	size_t len;

	if (*buf++ == '[')
	{
		if (*buf == ESC_KEY_RIGHT)
			if (can_move_cursor((*hst)->cmd, right))
				write(1, CURSOR_RIGHT, 3);
		if (*buf == ESC_KEY_LEFT)
			if (can_move_cursor((*hst)->cmd, left))
				write(1, CURSOR_LEFT, 3);
		if ((*buf == ESC_KEY_UP && (*hst)->prev) ||
			(*buf == ESC_KEY_DOWN && (*hst)->next))
		{
			len = ft_strlen((*hst)->cmd->raw);
			*hst = *buf == ESC_KEY_UP ? (*hst)->prev : (*hst)->next;
			move_cursor(left, len);
			fill_with(' ', len);
			move_cursor(left, len);
			write(1,(*hst)->cmd->raw, (*hst)->cmd->len);
			(*hst)->cmd->cpos = (*hst)->cmd->len;
		}
	}
}

// Main loop of input, reads and processes input, only returns the raw of cmd
char	*get_cmd(t_hst **hst)
{
	char	buf[5];

	push_back_hst(hst, new_cmd());
	while (true)
	{
		ft_memset(buf, 0, 5);
		read(0, &buf, 4);
		if (*buf == ESCAPE_KEY)
			cmd_arrows(hst, buf + 1);
		else if (*buf == RETURN_KEY)
			break;
		else if (*buf == BACKSPACE_KEY)
			cmd_backspace((*hst)->cmd);
		else if (*buf == CTRL_D_KEY && cmd_ctrld_shoould_exit((*hst)->cmd))
			break;
		else if (*buf == CTRL_U_KEY)
			cmd_ctrlu((*hst)->cmd);
		else
			cmd_character((*hst)->cmd, buf);
	}
	return (cmd_return(*hst));
}
