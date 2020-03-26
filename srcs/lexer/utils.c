/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 22:51:09 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/26 13:42:54 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"

t_lex_lst 	*lex_lstnew(void)
{
    t_lex_lst	*lst;

    if (!(lst = malloc(sizeof(t_lex_lst))))
		return (NULL);
    lst->raw = NULL;
    lst->token = 0;
    lst->next = NULL;
	lst->space = false;
    return (lst);
}

t_lex_lst	*tkn_dup(t_lex_lst **head, int token)
{
	t_lex_lst	*n_head;
	t_lex_lst	*cur;

	n_head = lex_lstnew();
	n_head->raw = (*head)->raw;
	n_head->token = (*head)->token;
	cur = n_head;
	*head = (*head)->next;
	while (*head && (*head)->token != token)
	{
		cur->next = lex_lstnew();
		cur = cur->next;
		cur->raw = (*head)->raw;
		cur->token = (*head)->token;
		*head = (*head)->next;
	}
	return (n_head);
}

t_lex_lst	**split_tkn_lst(t_lex_lst *head)
{
	t_lex_lst	*cur;
	t_lex_lst	**sp;
	int		i;
	int		j;

	cur = head;
	i = 1;
	while (cur)
	{
		if (cur->token == NEWLINE)
			i++;
		cur = cur->next;
	}
	sp = (t_lex_lst **)malloc(sizeof(t_lex_lst *) * i + 1);
	cur = head;
	j = 0;
	while (j < i)
	{
		sp[j++] = tkn_dup(&cur, NEWLINE);
		if (cur->token == NEWLINE)
			cur = cur->next;
	}
	sp[j] = NULL;
	return (sp);
}
