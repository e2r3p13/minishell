/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 13:49:00 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/29 19:37:35 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tokens.h"
#include "minishell.h"
#include <stdlib.h>

void	*g_ascii_tokens[256] =
{
	['<'] = lxr_redirect,
	['>'] = lxr_redirect,
	['|'] = lxr_redirect,
	['$'] = lxr_variable,
	[';'] = lxr_newline,
	['\n'] = lxr_newline,
	['\''] = lxr_quote,
	['\"'] = lxr_quote,
};

// The t_lxr struct is a linked list that represents a lexed command.
// It contains a 'raw' field (the portion of command), a 'token' field,
// (the kind of that portion) and a 'space' field that indicates weither the
// portion of command was separated of the next portion of command by a space.
// 'next' is the next element of the list.

// Main loop of the lexer, return the head of the list
t_lxr	*lexer(char *str)
{
	t_lxr	*head;
	t_lxr	*cur;
	int		(*f)(char *str, t_lxr *lst);

	if (!(head = lxr_lstnew()))
		return (NULL);
	cur = head;
	while (*str)
	{
		if (cur->token)
		{
			if (*str == ' ')
				cur->space = true;
			if (!(cur->next = lxr_lstnew()))
				return (lxr_free(head));
			cur = cur->next;
		}
		if (*str == ' ')
			str++;
		if (!(f = g_ascii_tokens[(int)*str]))
			f = lxr_word;
		str += f(str, cur);
	}
	cur = head;
	return (lxr_check_grammar(head));
}

// Check the grammar of the lexed command, before spliting it
t_lxr	*lxr_check_grammar(t_lxr *head)
{
	int			last_token;
	t_bool		is_cmd_valid;
	t_lxr	*tmp;

	last_token = NEWLINE;
	is_cmd_valid = true;
	tmp = head;
	while (tmp)
	{
		if ((tmp->token == NEWLINE || tmp->token == REDIRECT) &&
			(last_token == NEWLINE || last_token == REDIRECT))
				is_cmd_valid = false;
		last_token = tmp->token;
		tmp = tmp->next;
	}
	if (is_cmd_valid)
		return (head);
	lxr_free(head);
	write(1, "Invalid command\n", 16);
	return (NULL);
}


static void	lxr_pop(t_lxr *head, t_lxr **cur)
{
	while (head->next != *cur)
		head = head->next;
	head->next = (*cur)->next;
	free(*cur);
}
// Turns *t_lxr into **t_lxr, allowing us to execute each commands separately
t_lxr	**lxr_split(t_lxr *head)
{
	t_lxr	*cur;
	t_lxr	**sp;
	int			i;
	int			j;

	if (!(cur = head) || !(i = 1))
		return (NULL);
	while (cur)
	{
		if (*(cur->raw) == 0)//ugly fix
			lxr_pop(head, &cur);//ugly fix
		if (cur->token == NEWLINE && cur->next)
			i++;
		cur = cur->next;
	}
	if (!(sp = malloc(sizeof(t_lxr *) * (i + 1))))
		return (NULL);
	sp[i] = NULL;
	cur = head;
	j = 0;
	while (j < i)
		sp[j++] = lxr_get_cmd_head(&cur);
	return (sp);
}

// Utils for lxr_split()
t_lxr	*lxr_get_cmd_head(t_lxr **head)
{
	t_lxr	*head_save;
	t_lxr	*cmd_end;
	t_lxr	*nl_elm;

	cmd_end = NULL;
	head_save = (*head);
	while ((*head) && (*head)->token != NEWLINE)
	{
		cmd_end = (*head);
		(*head) = (*head)->next;
	}
	if ((*head) && (*head)->token == NEWLINE)
	{
		if (cmd_end)
			cmd_end->next = NULL;
		nl_elm = (*head);
		(*head) = (*head)->next;
		free(nl_elm->raw);
		free(nl_elm);
	}
	return (head_save);
}
