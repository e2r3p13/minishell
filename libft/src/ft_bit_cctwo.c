/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bit_cctwo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 14:00:51 by lfalkau           #+#    #+#             */
/*   Updated: 2019/10/26 14:00:52 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_bit_cctwo(char *oct)
{
	char	*noct;
	int		i;

	if (!(noct = malloc(sizeof(char) * 9)))
		return (NULL);
	i = 0;
	while (i < 8)
	{
		noct[i] = oct[i] == '1' ? '0' : '1';
		i++;
	}
	return (noct);
}
