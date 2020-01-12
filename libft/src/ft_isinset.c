/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isinset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 12:49:58 by lfalkau           #+#    #+#             */
/*   Updated: 2019/11/22 09:29:03 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool		ft_isinset(char const *set, char c)
{
	while (*set)
	{
		if (c == *set++)
			return (1);
	}
	return (0);
}
