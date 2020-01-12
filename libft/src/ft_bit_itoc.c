/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bit_itoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 13:56:56 by lfalkau           #+#    #+#             */
/*   Updated: 2019/11/03 11:20:41 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_bit_itoc(char nb)
{
	int		z;
	char	*oct;
	int		i;

	z = 128;
	if (!(oct = malloc(sizeof(char) * 9)))
		return (NULL);
	i = 0;
	while (z > 0)
	{
		if (nb & z)
			oct[i] = '1';
		else
			oct[i] = '0';
		z >>= 1;
		i++;
	}
	oct[i] = '\0';
	return (oct);
}
