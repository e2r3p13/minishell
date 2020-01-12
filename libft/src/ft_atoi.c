/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:37:20 by lfalkau           #+#    #+#             */
/*   Updated: 2019/10/22 00:58:35 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	nb;
	int	is_neg;
	int i;

	nb = 0;
	is_neg = 0;
	i = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == ' ')
		i++;
	if ((str[i] == '+' || str[i] == '-'))
		is_neg = (str[i++] == '-' ? 1 : 0);
	while (ft_isdigit(str[i]))
		nb = nb * 10 + (str[i++]) - '0';
	return (is_neg ? -nb : nb);
}
