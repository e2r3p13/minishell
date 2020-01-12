/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 20:00:06 by lfalkau           #+#    #+#             */
/*   Updated: 2019/11/14 00:09:01 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stddef.h>

char		*ft_realloc(char *line)
{
	int		len;
	char	*str;

	len = 0;
	while (line[len])
		len++;
	if (!(str = (char *)malloc(sizeof(char) * (len + BUFFER_SIZE + 1))))
		return (NULL);
	ft_memset(str, 0, len + BUFFER_SIZE + 1);
	ft_memcpy(str, line, len);
	free(line);
	return (str);
}
