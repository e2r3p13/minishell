/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynstr_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 21:36:08 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/08 21:44:28 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_dynstr	*dynstr_new(void)
{
	t_dynstr	*dstr;

	if ((dstr = malloc(sizeof(t_dynstr))))
	{
		if ((dstr->str = malloc(sizeof(char) * (DYNSTR_START_SIZE + 1))))
		{
			ft_memset(dstr->str, 0, sizeof(char) * (DYNSTR_START_SIZE + 1));
			dstr->capacity = DYNSTR_START_SIZE;
			dstr->len = 0;
			return (dstr);
		}
		free(dstr);
	}
	return (NULL);
}
