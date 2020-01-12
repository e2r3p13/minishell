/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 11:55:19 by lfalkau           #+#    #+#             */
/*   Updated: 2019/10/20 15:32:09 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*tmp;
	unsigned char	d;

	tmp = (unsigned char *)b;
	d = (unsigned char)c;
	while (len--)
		*tmp++ = d;
	return (b);
}
