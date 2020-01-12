/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:00:49 by lfalkau           #+#    #+#             */
/*   Updated: 2019/10/21 19:42:37 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;
	unsigned char		q;

	str = (const unsigned char *)s;
	q = (unsigned char)c;
	while (n--)
		if (*str++ == q)
			return ((void *)--str);
	return (NULL);
}
