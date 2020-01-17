/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 19:54:24 by lfalkau           #+#    #+#             */
/*   Updated: 2019/10/21 19:47:43 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;
	size_t	total_size;

	total_size = (count * size == 0) ? 1 : (count * size);
	if (!(mem = malloc(total_size)))
		return (NULL);
	ft_bzero(mem, total_size);
	return (mem);
}
