/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_spe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 15:07:08 by lfalkau           #+#    #+#             */
/*   Updated: 2020/05/11 13:16:27 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

int	handle_printables(t_dynstr *dstr, size_t *cpos, char *buf, t_hst **hst)
{
	hst += 0;
	while (ft_isprint(*buf) &&
		dynstr_insert_at(*cpos, dstr, *buf) == EXIT_SUCCESS)
	{
		write(1, buf, 1);
		*cpos += 1;
		if (*cpos < dstr->len)
		{
			write(1, dstr->str + *cpos, dstr->len - *cpos);
			move_cursor(left, dstr->len - *cpos);
		}
		buf++;
	}
	return (0);
}

int	handle_backspace(t_dynstr *dstr, size_t *cpos)
{
	size_t cpl;

	if (dynstr_remove_at(*cpos - 1, dstr) == EXIT_SUCCESS)
	{
		move_cursor(left, 1);
		cpl = dstr->len - *cpos + 1;
		write(1, dstr->str + *cpos - 1, cpl);
		write(1, " ", 1);
		move_cursor(left, cpl + 1);
		*cpos -= 1;
	}
	return (0);
}

int	handle_del(t_dynstr *dstr, size_t *cpos)
{
	move_cursor(right, 1);
	*cpos += 1;
	handle_backspace(dstr, cpos);
	return (0);
}

int	handle_return(t_dynstr *dstr, size_t *cpos, char *buf, t_hst **hst)
{
	*cpos += (size_t)buf;
	if ((*hst)->next)
		hst_replace_last(hst, dstr);
	if (dstr->len)
		hst_save(dstr->str);
	write(1, "\n", 1);
	return (1);
}

int	handle_escape(t_dynstr *dstr, size_t *cpos, char *buf, t_hst **hst)
{
	buf++;
	if (ft_strcmp(buf, "[D") == 0 && *cpos > 0)
		return (handle_arrow(NULL, cpos, left));
	if (ft_strcmp(buf, "[C") == 0 && *cpos < dstr->len)
		return (handle_arrow(dstr, cpos, right));
	if (ft_strcmp(buf, "[A") == 0)
		return (handle_history(dstr, cpos, hst, up));
	if (ft_strcmp(buf, "[B") == 0)
		return (handle_history(dstr, cpos, hst, down));
	if (ft_strcmp(buf, "OH") == 0 || ft_strcmp(buf, "[H") == 0)
		return (handle_fnarrow(dstr, cpos, left));
	if (ft_strcmp(buf, "OF") == 0 || ft_strcmp(buf, "[F") == 0)
		return (handle_fnarrow(dstr, cpos, right));
	if (ft_strcmp(buf, "b") == 0 || ft_strcmp(buf, "\033[D") == 0)
		return (handle_optleft(dstr, cpos));
	if (ft_strcmp(buf, "f") == 0 || ft_strcmp(buf, "\033[C") == 0)
		return (handle_optright(dstr, cpos));
	if (ft_strcmp(buf, "[3~") == 0 && *cpos < dstr->len)
		handle_del(dstr, cpos);
	return (0);
}
