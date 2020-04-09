/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynstr_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 21:46:08 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/08 22:47:56 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dynstr	*dynstr_join(t_dynstr *ds1, t_dynstr *ds2)
{
	t_dynstr	*new_dstr;
	size_t		i;

	if ((new_dstr = dynstr_new()))
	{
		i = 0;
		while (ds1->str[i])
			dynstr_push(new_dstr, ds1->str[i++]);
		i = 0;
		while (ds2->str[i])
			dynstr_push(new_dstr, ds2->str[i++]);
		return (new_dstr);
	}
	return (NULL);
}
