/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_addback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 13:41:20 by lfalkau           #+#    #+#             */
/*   Updated: 2019/11/14 00:19:53 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_ls **alst, t_ls *new)
{
	t_ls *tmp;

	if (!alst || !new)
		return ;
	tmp = ft_lstlast(*alst);
	if (!tmp)
		*alst = new;
	else
		tmp->next = new;
}
