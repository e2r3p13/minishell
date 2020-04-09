/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynstr_insert_at.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 21:45:44 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/09 09:24:01 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	dynstr_insert_at(size_t i, t_dynstr *dstr, char c)
{
	size_t	j;

	if (i > dstr->len)
		return (EXIT_FAILURE);
	if (dstr->len == dstr->capacity && dynstr_realloc(dstr) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	j = dstr->len;
	while (j > i)
	{
		dstr->str[j] = dstr->str[j - 1];
		j--;
	}
	dstr->str[j] = c;
	dstr->len++;
	return (EXIT_SUCCESS);
}
