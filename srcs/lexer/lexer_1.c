/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 17:46:10 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/02 09:58:14 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"

// The t_lxr struct is a linked list that represents a lexed command.
// It contains a 'raw' field (the portion of command), a 'token' field,
// (the kind of that portion) and a 'space' field that indicates weither the
// portion of command was separated of the next portion of command by a space.
// 'next' is the next element of the list.

// Return an initialized t_lxr element
t_lxr 	*lxr_lstnew(void)
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

// Free the lexed list, from head to the last element
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

// Return the length of a lexer list
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

// Temporary function, printing the t_lxr array
void	lxr_print(t_lxr **lst)
{
	int			i;
	t_lxr	*cur;

	i = 0;
	while (lst[i])
	{
		cur = lst[i];
		printf("Cmd n° %d:\n", i + 1);
		while (cur)
		{
			printf("token: %d | raw: %s | spaced: %d\n",
			cur->token, cur->raw, cur->space);
			cur = cur->next;
		}
		printf("-------------\n");
		i++;
	}
}
