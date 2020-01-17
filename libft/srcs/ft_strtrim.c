/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:49:10 by lfalkau           #+#    #+#             */
/*   Updated: 2019/10/21 16:31:25 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

static int		is_in_set(char const *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	size_t	start_index;
	size_t	end_index;

	if (!s1 || !set)
		return (NULL);
	if (!(end_index = ft_strlen(s1)))
		return (ft_strdup(""));
	end_index--;
	start_index = 0;
	while (is_in_set(set, s1[start_index]))
		start_index++;
	while (is_in_set(set, s1[end_index]) && end_index)
		end_index--;
	if (end_index < start_index)
		return (ft_strdup(""));
	return (ft_substr(s1, start_index, end_index - start_index + 1));
}
