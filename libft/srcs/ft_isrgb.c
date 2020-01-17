/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isrgb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 09:12:32 by lfalkau           #+#    #+#             */
/*   Updated: 2019/11/22 09:30:27 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_isrgb(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		if (!ft_isstrdigit(array[i]) || ft_atoi(array[i]) > 255)
			return (false);
		i++;
	}
	return (i == 3 ? true : false);
}
