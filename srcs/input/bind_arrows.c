/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_arrows.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 15:04:47 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/11 10:56:30 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int	handle_arrow(t_dynstr *dstr, size_t *cpos, t_dir dir)
{
	dstr += 0;
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
	if ((dir == up && !(*hst)->prev) || (dir == down && !(*hst)->next))
		return (0);
	move_cursor(left, *cpos);
	writen(' ', dstr->len);
	move_cursor(left, dstr->len);
	*hst = (dir == up ? (*hst)->prev : (*hst)->next);
	dstr->str = (*hst)->cmd;
	dstr->len = ft_strlen(dstr->str);
	dstr->capacity = dstr->len;
	write(1, dstr->str, dstr->len);
	*cpos = dstr->len;
	return (0);
}
