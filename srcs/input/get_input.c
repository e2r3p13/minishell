/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 14:54:24 by lfalkau           #+#    #+#             */
/*   Updated: 2020/05/11 13:21:23 by lfalkau          ###   ########.fr       */
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
	[CTRLC] = &handle_ctrlc,
	[CTRLD] = &handle_ctrld,
	[CTRLH] = &handle_ctrlh,
	[TAB] = &handle_tab,
	[RETURN] = &handle_return,
	[CTRLK] = &handle_ctrlk,
	[CTRLN] = &handle_ctrln,
	[CTRLP] = &handle_ctrlp,
	[CTRLU] = &handle_ctrlu,
	[ESCAPE] = &handle_escape,
	[BACKSPACE] = &handle_backspace,
};

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
			bindf = &handle_printables;
		if (bindf(dstr, &cpos, buf, hst) == 1 && ((*hst)->cmd = dstr->str))
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
