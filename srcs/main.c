/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 15:13:41 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/10 11:27:14 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **e)
{
	struct stat	stat;
	t_env		*env;
	t_hst		*hst;

	av[ac] = NULL;
	signal(SIGINT, sighandler);
	signal(SIGKILL, sighandler);
	if (!(env = env_get(e)))
		return (EXIT_FAILURE);
	fstat(0, &stat);
	if (S_ISCHR(stat.st_mode))
	{
		hst = hst_get();
		minishell(env, hst, true);
		hst_free(hst);
	}
	else
	{
		minishell(env, NULL, false);
	}
	return (EXIT_SUCCESS);
}

void sighandler(int sig)
{
	signal(sig, SIG_IGN);
}
