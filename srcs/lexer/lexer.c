/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 13:49:00 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/26 00:23:47 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tokens.h"
#include "minishell.h"
#include <stdlib.h>

void	*g_ascii_tokens[256] =
{
	['<'] = lex_redirect,
	['>'] = lex_redirect,
	['|'] = lex_redirect,
	['$'] = lex_variable,
	[';'] = lex_newline,
	['\n'] = lex_newline,
	['\''] = lex_quote,
	['\"'] = lex_quote,
};

t_lex_lst	*lexer(char *str)
{
	t_lex_lst	*head;
	t_lex_lst	*cur;
	int			(*f)(char *str, t_lex_lst *lst);

	head = lex_lstnew();
	cur = head;
	while (*str)
	{
		if (cur->token)
		{
			if (*str == ' ')
				cur->space = true;
			cur->next = lex_lstnew();
			cur = cur->next;
		}
		if (*str == ' ')
			str++;
		if (!(f = g_ascii_tokens[(int)*str]))
			f = lex_word;
		str += f(str, cur);
	}
	return (head);
}
