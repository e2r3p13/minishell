/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_ctrl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 14:57:55 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/10 17:27:33 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "keys.h"
#include <stdlib.h>
#include <unistd.h>

int		handle_ctrld(char *buf, size_t *cpos, t_dynstr *dstr)
{
	if (*cpos == 0 && dstr->len == 0 && dynstr_push(dstr, EOI) == EXIT_SUCCESS)
	{
		write(1, "exit\n", 5);
		return (1);
	}
	else if (*cpos < dstr->len)
		return (handle_del(buf, cpos, dstr));
	return (0);
}

int		handle_ctrlc(char *buf, size_t *cpos, t_dynstr *dstr)
{
	buf = NULL;
	cpos = NULL;
	dynstr_clear(dstr);
	write(1, "\n", 1);
	return (1);
}

int		handle_ctrlu(char *buf, size_t *cpos, t_dynstr *dstr)
{
	buf = NULL;
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

int		handle_ctrlk(char *buf, size_t *cpos, t_dynstr *dstr)
{
	while (*cpos < dstr->len)
		handle_del(buf, cpos, dstr);
	return (0);
}

int		handle_ctrlh(char *buf, size_t *cpos, t_dynstr *dstr)
{
	while (*cpos)
		handle_backspace(buf, cpos, dstr);
	return (0);
}
