/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 13:49:00 by lfalkau           #+#    #+#             */
/*   Updated: 2020/05/16 16:48:02 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

extern int g_exitcode;

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

t_lxr		*lexer(char *str)
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
		if (!(f = g_ascii_tokens[(int)*str]))
			f = lxr_word;
		str += *str == ' ' ? 1 : f(str, cur);
	}
	cur = head;
	return (lxr_check_grammar(head));
}

t_lxr		*lxr_check_grammar(t_lxr *head)
{
	int			lt;
	t_bool		is_cmd_valid;
	t_lxr		*t;

	lt = NEWLINE;
	is_cmd_valid = true;
	t = head;
	while (t)
	{
		if ((t->token == NEWLINE || t->token == REDIRECT || t->token == PIPE) &&
			(lt == NEWLINE || lt == REDIRECT || lt == PIPE))
			is_cmd_valid = false;
		if (lt == NEWLINE && t->token == WORD && (t->space || !t->next))
			replace_alias(t);
		lt = t->token;
		t = t->next;
	}
	if (lt != REDIRECT && lt != PIPE && is_cmd_valid)
		return (head);
	lxr_free(head);
	write(1, "minishell: Invalid command\n", 27);
	g_exitcode = 258;
	return (NULL);
}

static int	lxr_pop(t_lxr *head, t_lxr **cur)
{
	if (head == *cur)
	{
		*cur = (*cur)->next;
		free(head->raw);
		free(head);
		if (*cur == NULL)
			return (EXIT_FAILURE);
	}
	else
	{
		while (head && head->next != *cur)
			head = head->next;
		head->next = (*cur)->next;
		free((*cur)->raw);
		free(*cur);
		(*cur) = head->next;
	}
	return (EXIT_SUCCESS);
}

t_lxr		**lxr_split(t_lxr *head)
{
	t_lxr	*cur;
	t_lxr	**sp;
	int		i;
	int		j;

	i = 1;
	if (!(cur = head))
		return (NULL);
	while (cur)
	{
		if (cur && cur->raw == NULL && lxr_pop(head, &cur) == EXIT_FAILURE)
			return (NULL);
		if (cur && cur->token == NEWLINE && cur->next)
			i++;
		if (cur)
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

t_lxr		*lxr_get_cmd_head(t_lxr **head)
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
