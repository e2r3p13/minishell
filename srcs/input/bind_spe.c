/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_spe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 15:07:08 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/09 19:50:55 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int		handle_printable_char(char *buf, size_t *cpos, t_dynstr *dstr)
{
	while (ft_isprint(*buf) && dynstr_insert_at(*cpos, dstr, *buf) == EXIT_SUCCESS)
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

int		handle_backspace(char *buf, size_t *cpos, t_dynstr *dstr)
{
	size_t cpl;

	buf = NULL;
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

int		handle_del(char *buf, size_t *cpos, t_dynstr *dstr)
{
	move_cursor(right, 1);
	*cpos += 1;
	handle_backspace(buf, cpos, dstr);
	return (0);
}

int		handle_return(char *buf, size_t *cpos, t_dynstr *dstr)
{
	buf = NULL;
	cpos = NULL;
	dstr = NULL;
	write(1, "\n", 1);
	return (1);
}

int		handle_escape(char *buf, size_t *cpos, t_dynstr *dstr)
{
	buf++;
	if (ft_strcmp(buf, "[D") == 0 && *cpos > 0)
		return (handle_arrow(buf, cpos, dstr, left));
	if (ft_strcmp(buf, "[C") == 0 && *cpos < dstr->len)
		return (handle_arrow(buf, cpos, dstr, right));
	if (ft_strcmp(buf, "[A") == 0)
		return (handle_history(buf, cpos, dstr, up));
	if (ft_strcmp(buf, "[B") == 0)
		return (handle_history(buf, cpos, dstr, down));
	if (ft_strcmp(buf, "OH") == 0)
		return (handle_fnarrow(buf, cpos, dstr, left));
	if (ft_strcmp(buf, "OF") == 0)
		return (handle_fnarrow(buf, cpos, dstr, right));
	if (ft_strcmp(buf, "b") == 0)
		return (handle_optleft(buf, cpos, dstr));
	if (ft_strcmp(buf, "f") == 0)
		return (handle_optright(buf, cpos, dstr));
	if (ft_strcmp(buf, "[3~") == 0 && *cpos < dstr->len)
		handle_del(buf, cpos, dstr);
	return (0);
}
