/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynstr_from_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 23:02:04 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/08 23:04:56 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dynstr	*dynstr_from_str(char *s)
{
	t_dynstr	*dstr;

	if ((dstr = dynstr_new()))
	{
		while (*s)
			dynstr_push(dstr, *s++);
		return (dstr);
	}
	return (NULL);
}
