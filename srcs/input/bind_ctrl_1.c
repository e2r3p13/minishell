/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_ctrl_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 17:08:26 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/11 17:13:29 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_ctrlp(t_dynstr *dstr, size_t *cpos, char *buf, t_hst **hst)
{
	buf += 0;
	return (handle_history(dstr, cpos, hst, up));
}

int	handle_ctrln(t_dynstr *dstr, size_t *cpos, char *buf, t_hst **hst)
{
	buf += 0;
	return (handle_history(dstr, cpos, hst, down));
}
