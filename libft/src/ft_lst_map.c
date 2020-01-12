/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 13:43:31 by lfalkau           #+#    #+#             */
/*   Updated: 2019/11/14 00:20:06 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

t_ls	*ft_lstmap(t_ls *lst, void *(*f)(void *), void (*del)(void *))
{
	t_ls *new;
	t_ls *tmp;

	if (!f || !lst || !del)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	if (!new)
		return (NULL);
	tmp = new;
	while (lst->next)
	{
		lst = lst->next;
		tmp->next = ft_lstnew(f(lst->content));
		tmp = tmp->next;
		if (!tmp)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
	}
	return (new);
}
