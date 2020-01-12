/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_spaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 09:11:27 by lfalkau           #+#    #+#             */
/*   Updated: 2019/11/22 09:21:06 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char		*ft_remove_spaces(char *str)
{
	int		i;
	int		len;
	char	*new_str;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			len++;
		i++;
	}
	if (!(new_str = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	new_str[len] = '\0';
	i = 0;
	while (*str)
	{
		if (*str != ' ')
			new_str[i++] = *str;
		str++;
	}
	return (new_str);
}
