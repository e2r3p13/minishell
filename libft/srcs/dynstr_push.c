/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynstr_push.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 21:45:21 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/08 22:45:28 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	dynstr_push(t_dynstr *dstr, char c)
{
	if (dstr->len == dstr->capacity && dynstr_realloc(dstr) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	dstr->str[dstr->len] = c;
	dstr->len++;
	return (EXIT_SUCCESS);
}
