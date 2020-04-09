/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynstr_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 21:44:56 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/08 22:48:50 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	dynstr_clear(t_dynstr *dstr)
{
	ft_memset(dstr->str, 0, sizeof(char) * dstr->len);
	dstr->len = 0;
}
