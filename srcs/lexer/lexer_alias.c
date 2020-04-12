/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_alias.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 14:06:15 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/12 14:15:04 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

extern t_als	*g_als;

static void	lxr_split_token(t_lxr *lxr, char **arr)
{
	t_lxr	*end;
	t_lxr	*tmp;
	int		i;

	end = lxr->next;
	i = -1;
	while (arr[++i])
	{
		if (i == 0)
		{
			free(lxr->raw);
			lxr->raw = arr[0];
			lxr->space = true;
			continue ;
		}
		if (!(tmp = lxr_lstnew()))
			break ;
		lxr->next = tmp;
		tmp->raw = arr[i];
		lxr = tmp;
		tmp->space = true;
	}
	lxr->next = end;
}

void		replace_alias(t_lxr *lxr)
{
	t_als	*als;
	char	**rep;

	als = g_als;
	while (als)
	{
		if (ft_strcmp(lxr->raw, als->key) == 0)
		{
			if ((rep = ft_split(als->value, ' ')))
			{
				lxr_split_token(lxr, rep);
				free(rep);
				break ;
			}
		}
		als = als->next;
	}
}
