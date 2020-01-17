/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:42:22 by lfalkau           #+#    #+#             */
/*   Updated: 2019/10/18 10:44:17 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_pow_finder(unsigned int nbr)
{
	int pow;

	pow = 0;
	while (nbr > 9)
	{
		nbr /= 10;
		pow++;
	}
	return (pow);
}

char		*ft_itoa(int n)
{
	char			*n_str;
	unsigned int	nbr;
	int				pow;
	int				is_neg;
	int				size;

	is_neg = (n < 0 ? 1 : 0);
	nbr = is_neg ? -n : n;
	pow = ft_pow_finder(nbr);
	size = is_neg ? pow + 1 : pow;
	if (!(n_str = (char *)malloc(sizeof(char) * (size + 2))))
		return (NULL);
	if (is_neg)
		n_str[0] = '-';
	n_str[size + 1] = '\0';
	while (pow >= 0)
	{
		n_str[size] = nbr % 10 + '0';
		nbr /= 10;
		size--;
		pow--;
	}
	return (n_str);
}
