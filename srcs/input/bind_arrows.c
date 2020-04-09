/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_arrows.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 15:04:47 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/09 19:57:30 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int		handle_arrow(char *buf, size_t *cpos, t_dynstr *dstr, t_dir dir)
{
	buf = NULL;
	dstr = NULL;
	if (dir == left)
	{
		move_cursor(left, 1);
		*cpos -= 1;
	}
	else
	{
		move_cursor(right, 1);
		*cpos += 1;
	}
	return (0);
}

int		handle_fnarrow(char *buf, size_t *cpos, t_dynstr *dstr, t_dir dir)
{
	buf = NULL;
	if (dir == left)
	{
		move_cursor(left, *cpos);
		*cpos = 0;
	}
	else
	{
		move_cursor(right, dstr->len - *cpos);
		*cpos = dstr->len;
	}
	return (0);
}

int		handle_optleft(char *buf, size_t *cpos, t_dynstr *dstr)
{
	buf = NULL;
	while (*cpos && dstr->str[*cpos - 1] == ' ')
	{
		move_cursor(left, 1);
		*cpos -= 1;
	}
	while (*cpos && dstr->str[*cpos - 1] != ' ')
	{
		move_cursor(left, 1);
		*cpos -= 1;
	}
	return (0);
}

int		handle_optright(char *buf, size_t *cpos, t_dynstr *dstr)
{
	buf = NULL;
	while (dstr->str[*cpos] && dstr->str[*cpos] != ' ')
	{
		move_cursor(right, 1);
		*cpos += 1;
	}
	while (dstr->str[*cpos] && dstr->str[*cpos] == ' ')
	{
		move_cursor(right, 1);
		*cpos += 1;
	}
	return (0);
}

int		handle_history(char *buf, size_t *cpos, t_dynstr *dstr, t_dir dir)
{
	buf = NULL;
	cpos = NULL;
	dstr = NULL;
	dir = up;
	return (0);
}

/*
** size_t	len;
** size_t	pos;
**
** len = (*hst)->cmd->len;
** pos = (*hst)->cmd->pos;
** *hst = key == KEY_UP ? (*hst)->prev : (*hst)->next;
** term_move_cursor(left, pos);
** term_writen(' ', len);
** term_move_cursor(left, len);
** write(1, (*hst)->cmd->raw, (*hst)->cmd->len);
** (*hst)->cmd->pos = (*hst)->cmd->len;
*/
