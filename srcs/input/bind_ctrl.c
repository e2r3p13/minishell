/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_ctrl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 14:57:55 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/10 20:47:50 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "keys.h"
#include <stdlib.h>
#include <unistd.h>

int	handle_ctrld(t_dynstr *dstr, size_t *cpos)
{
	if (*cpos == 0 && dstr->len == 0 && dynstr_push(dstr, EOI) == EXIT_SUCCESS)
	{
		write(1, "exit\n", 5);
		return (1);
	}
	else if (*cpos < dstr->len)
		return (handle_del(dstr, cpos));
	return (0);
}

int	handle_ctrlc(t_dynstr *dstr)
{
	dynstr_clear(dstr);
	write(1, "\n", 1);
	return (1);
}

int	handle_ctrlu(t_dynstr *dstr, size_t *cpos)
{
	move_cursor(left, *cpos);
	if (writen(' ', dstr->len) == EXIT_SUCCESS)
	{
		move_cursor(left, dstr->len);
		dynstr_clear(dstr);
		*cpos = 0;
	}
	else
		move_cursor(right, *cpos);
	return (0);
}

int	handle_ctrlk(t_dynstr *dstr, size_t *cpos)
{
	while (*cpos < dstr->len)
		handle_del(dstr, cpos);
	return (0);
}

int	handle_ctrlh(t_dynstr *dstr, size_t *cpos)
{
	while (*cpos)
		handle_backspace(dstr, cpos);
	return (0);
}
