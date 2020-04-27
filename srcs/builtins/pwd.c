/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 16:45:43 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/27 12:34:02 by bccyv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

int	ms_pwd(int ac, char **av)
{
	char *cwd;

	av[ac] = NULL;
	if ((cwd = getcwd(NULL, 0)))
	{
		write(1, cwd, ft_strlen(cwd));
		write(1, "\n", 1);
		free (cwd);
		return (EXIT_SUCCESS);
	}
	write(1, "cd: An error occured while getting cwd\n", 39);
	return (EXIT_FAILURE);
}
