/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 13:43:23 by lfalkau           #+#    #+#             */
/*   Updated: 2019/11/14 00:20:09 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_ls	*ft_lstnew(void *content)
{
	t_ls *lst;

	if (!(lst = (t_ls *)malloc(sizeof(t_ls))))
		return (NULL);
	lst->content = content;
	lst->next = NULL;
	return (lst);
}
