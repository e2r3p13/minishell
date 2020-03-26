/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 13:49:00 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/26 18:28:48 by lfalkau          ###   ########.fr       */
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

t_lex_lst	*lexer(char *str, char **env)
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
	cur = head;
	return (head);
}

t_bool	expand(t_lex_lst *lst, char **env)
{
	t_lex_lst	*save;

	save = lst;
	while (lst)
	{
		if (lst->token == DQUOTE && !expand_dquotes(lst, env))
			return (false);
		if (lst->token == SQUOTE && !expand_squotes(lst))
			return (false);
		if (lst->token == VARIABLE)
			 lst->raw = expand_variable(lst->raw, env);
		if (lst->token == EXITCODE)
 			lst->raw = expand_exitcode(lst->raw);
		if (lst->token != REDIRECT && lst->token != NEWLINE)
			lst->token = WORD;
		lst = lst->next;
	}
	join_unspaced_words(save);
	return (true);
}

void	join_unspaced_words(t_lex_lst *lst)
{
	void	*tmp;

	while (lst)
	{
		if (lst->space == false && lst->next && lst->next->token == WORD)
		{
			tmp = lst->raw;
			lst->raw = ft_strjoin(tmp, lst->next->raw);
			free(tmp);
			if (lst->next)
				lst->space = lst->next->space;
			tmp = lst->next;
			lst->next = lst->next->next;
			free(tmp);
		}
		else
			lst = lst->next;
	}
}
