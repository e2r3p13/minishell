/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_wc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 18:01:27 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/26 15:32:29 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

int	ft_strncmp_wc(const char *s1, const char *s2, size_t n)
{
	unsigned long i;

	i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] == s2[i])
			i++;
		else if (ft_isalpha(s1[i]) && (s1[i] - s2[i] == 32 ||
			s2[i] - s1[i] == 32))
			i++;
		else
			break ;
	}
	return (i == n ? 0 : ((unsigned char)s1[i] - (unsigned char)s2[i]));
}
