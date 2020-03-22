/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/22 18:27:18 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/22 18:43:24 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
    size_t  len;
    char    *sd;

    len = ft_strlen(s) > n ? n : ft_strlen(s);
    if (!(sd = malloc(sizeof(char) * (len + 1))))
            return (NULL);
    ft_memcpy(sd, s, len);
	sd[len] = 0;
	return (sd);
}
