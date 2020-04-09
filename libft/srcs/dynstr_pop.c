/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynstr_pop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 21:45:29 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/09 20:54:56 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	dynstr_pop(t_dynstr *dstr)
{
	if (dstr->len < 1)
		return (EXIT_FAILURE);
	dstr->str[dstr->len - 1] = 0;
	dstr->len--;
	return (EXIT_SUCCESS);
}
