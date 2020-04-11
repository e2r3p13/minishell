/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 14:54:24 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/11 10:03:49 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "keys.h"
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

struct termios	g_oldterm;

void			*g_bind_ascii[128] =
{
	[3] = &handle_ctrlc,
	[4] = &handle_ctrld,
	[8] = &handle_ctrlh,
	[9] = &handle_tab,
	[10] = &handle_return,
	[11] = &handle_ctrlk,
	[21] = &handle_ctrlu,
	[27] = &handle_escape,
	[127] = &handle_backspace,
};

/*
**	[1] = &handle_ctrla,
**	[2] = &handle_ctrlb,
**	[5] = &handle_ctrle,
**	[6] = &handle_ctrlf,
**	[7] = &handle_ctrlg,
**	[9] = &handle_ctrli,
**	[12] = &handle_ctrll,
**	[14] = &handle_ctrln,
**	[16] = &handle_ctrlp,
**	[18] = &handle_ctrlr,
**	[20] = &handle_ctrlt,
**	[23] = &handle_ctrlw,
**	[24] = &handle_ctrlx,
*/

char		*get_it_cmd(t_hst **hst)
{
	t_dynstr	*dstr;
	size_t		cpos;
	char		buf[5];
	int			(*bindf)(t_dynstr *dstr, size_t *cpos, char *buf, t_hst **hst);

	if (!(dstr = dynstr_new()))
		return (NULL);
	hst_push(hst, dstr->str);
	cpos = 0;
	enable_raw_mode();
	while (true)
	{
		ft_memset(buf, 0, 5);
		read(0, buf, 4);
		if (*buf < 0)
			continue ;
		if (!(bindf = g_bind_ascii[(int)*buf]))
			bindf = &handle_printable_char;
		if (bindf(dstr, &cpos, buf, hst) == 1)
			break ;
		(*hst)->cmd = dstr->str;
	}
	disable_raw_mode();
	free(dstr);
	return ((*hst)->cmd);
}

char		*get_cmd(void)
{
	char *str;

	str = NULL;
	if (get_next_line(0, &str) != 0)
		return (str);
	else
	{
		if (!(str = malloc(sizeof(char) * 2)))
			return (NULL);
		*str = EOI;
		*(str + 1) = 0;
		return (str);
	}
}
