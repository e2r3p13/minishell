/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_arrows.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 15:04:47 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/10 20:49:46 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_arrow(t_dynstr *dstr, size_t *cpos, t_dir dir)
{
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

int	handle_fnarrow(t_dynstr *dstr, size_t *cpos, t_dir dir)
{
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

int	handle_optleft(t_dynstr *dstr, size_t *cpos)
{
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

int	handle_optright(t_dynstr *dstr, size_t *cpos)
{
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

int	handle_history(t_dynstr *dstr, size_t *cpos, t_hst **hst, t_dir dir)
{
	cpos = NULL;
	dstr = NULL;
	hst = NULL;
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
