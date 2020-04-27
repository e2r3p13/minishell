/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bccyv <bccyv@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 12:22:02 by bccyv             #+#    #+#             */
/*   Updated: 2020/04/27 12:27:44 by bccyv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

int	ms_exit(void)
{
  write(1, "exit\n", 5);
  return (EXIT_RETURN_VALUE);
}
