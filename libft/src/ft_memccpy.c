/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 12:49:25 by lfalkau           #+#    #+#             */
/*   Updated: 2019/11/10 13:02:13 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t len)
{
	size_t					i;
	unsigned char			*d;
	const unsigned char		*s;
	unsigned char			q;

	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	q = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		d[i] = s[i];
		if (s[i] == q)
			return (d + i + 1);
		i++;
	}
	return (NULL);
}
