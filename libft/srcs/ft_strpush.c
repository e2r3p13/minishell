/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 20:39:02 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/09 20:55:09 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strpush(char *str, char c)
{
	char	*tmp;
	int		len;

	len = ft_strlen(str);
	if (!(tmp = malloc(sizeof(char) * (len + 2))))
		return (str);
	ft_memcpy(tmp, str, len);
	tmp[len] = c;
	tmp[len + 1] = 0;
	free(str);
	return (tmp);
}
