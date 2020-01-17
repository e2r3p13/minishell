/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:58:35 by lfalkau           #+#    #+#             */
/*   Updated: 2019/10/20 16:05:14 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dlen;
	size_t	slen;

	i = 0;
	slen = ft_strlen(src);
	while (*dst && i++ < size)
		dst++;
	if (i - size - 1 == 0)
		return (--i + slen);
	dlen = i;
	while (*src && i++ < size - 1)
		*dst++ = *src++;
	*dst = 0;
	return (dlen + slen);
}
