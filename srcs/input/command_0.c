/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 00:35:57 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/08 20:26:33 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "keys.h"

extern struct termios	g_save;

t_cmd	*cmd_get(t_env *env, t_hst **hst)
{
	char	buf[5];

	prompt(env);
	if (!(hst_push_cmd(hst, cmd_new())))
		return (NULL);
	while (true)
	{
		ft_memset(buf, 0, 5);
		read(0, &buf, 4);
		if (*buf == ESCAPE_KEY && *(buf + 1) == '[')
			cmd_esc_seq(hst, buf + 2);
		else if (*buf == RETURN_KEY)
			break ;
		else if (*buf == BACKSPACE_KEY)
			cmd_handle_backspace((*hst)->cmd);
		else if (*buf == CTRL_D_KEY && cmd_handle_ctrld((*hst)->cmd))
			break ;
		else if (*buf == CTRL_U_KEY)
			cmd_handle_ctrlu((*hst)->cmd);
		else if (*buf == TAB_KEY)
			cmd_handle_tab((*hst)->cmd);
		else if (*buf)
			cmd_handle_character((*hst)->cmd, buf);
	}
	return (cmd_handle_return(*hst));
}

t_cmd	*cmd_handle_return(t_hst *hst)
{
	if (hst->next)
		hst_reuse_cmd(&hst, hst->cmd);
	cmd_save(hst->cmd);
	write(1, "\n", 1);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_save);
	return (hst->cmd);
}

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

void	cmd_handle_ctrlu(t_cmd *cmd)
{
	term_move_cursor(left, cmd->pos);
	term_writen(' ', cmd->len);
	term_move_cursor(left, cmd->len);
	cmd_erase(cmd);
}
