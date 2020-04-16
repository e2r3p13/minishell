/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 13:49:00 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/16 17:06:51 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "minishell.h"
#include <unistd.h>
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
	int			last_token;
	t_bool		is_cmd_valid;
	t_lxr		*tmp;

	last_token = NEWLINE;
	is_cmd_valid = true;
	tmp = head;
	while (tmp)
	{
		if ((tmp->token == NEWLINE || tmp->token == REDIRECT) &&
			(last_token == NEWLINE || last_token == REDIRECT))
			is_cmd_valid = false;
		if (last_token == NEWLINE && tmp->token == WORD &&
			(tmp->space || !tmp->next))
			replace_alias(tmp);
		last_token = tmp->token;
		tmp = tmp->next;
	}
	if (last_token != REDIRECT && is_cmd_valid)
		return (head);
	lxr_free(head);
	write(1, "Invalid command\n", 16);
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
