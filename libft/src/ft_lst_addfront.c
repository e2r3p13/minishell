/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_addfront.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 13:41:53 by lfalkau           #+#    #+#             */
/*   Updated: 2019/11/14 00:19:51 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_ls **alst, t_ls *new)
{
	if (!new || !alst)
		return ;
	new->next = *alst;
	*alst = new;
}
