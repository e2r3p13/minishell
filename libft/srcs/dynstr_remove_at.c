/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynstr_remove_at.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 21:45:55 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/09 11:18:04 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	dynstr_remove_at(size_t i, t_dynstr *dstr)
{
	if (dstr->len < 1 || i > dstr->len)
		return (EXIT_FAILURE);
	while (i <= dstr->len)
	{
		dstr->str[i] = dstr->str[i + 1];
		i++;
	}
	dstr->len--;
	return (EXIT_SUCCESS);
}
