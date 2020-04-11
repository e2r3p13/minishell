/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynstr_realloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 21:45:10 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/11 09:42:24 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	dynstr_realloc(t_dynstr *dstr)
{
	char	*new_str;
	size_t	new_capacity;

	new_capacity = dstr->capacity ? dstr->capacity * 2 : DYNSTR_START_SIZE;
	if ((new_str = malloc(sizeof(char) * (new_capacity + 1))))
	{
		ft_memset(new_str, 0, sizeof(char) * (new_capacity + 1));
		ft_memcpy(new_str, dstr->str, dstr->len);
		free(dstr->str);
		dstr->str = new_str;
		dstr->capacity = new_capacity;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
