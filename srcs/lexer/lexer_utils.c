/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 17:46:10 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/13 21:45:27 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"
#include <stdlib.h>

/*
** The t_lxr struct is a linked list that represents a lexed command.
** It contains a 'raw' field (the portion of command), a 'token' field,
** (the kind of that portion) and a 'space' field that indicates weither the
** portion of command was separated of the next portion of command by a space.
** 'next' is the next element of the list.
*/

t_lxr	*lxr_lstnew(void)
{
	t_lxr	*lst;

	if (!(lst = malloc(sizeof(t_lxr))))
		return (NULL);
	lst->raw = NULL;
	lst->token = 0;
	lst->next = NULL;
	lst->space = false;
	return (lst);
}

void	lxr_append(t_lxr **tail)
{
	(*tail)->next = lxr_lstnew();
	*tail = (*tail)->next;
}

void	*lxr_free(t_lxr *head)
{
	t_lxr *n;

	while (head)
	{
		n = head;
		head = head->next;
		if (n->raw)
			free(n->raw);
		free(n);
	}
	return (NULL);
}

int		lstsize(t_lxr *lst)
{
	int i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int		lxr_cmdsize(t_lxr *lst)
{
	int i;

	i = 0;
	while (lst && lst->token == WORD)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
