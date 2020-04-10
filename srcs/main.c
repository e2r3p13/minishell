/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 15:13:41 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/09 20:17:27 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hst	*g_hst = NULL;

int	main(int ac, char **av, char **e)
{
	struct stat	st;
	t_env		*env;

	av[ac] = NULL;
	signal(SIGINT, sighandler);
	signal(SIGKILL, sighandler);
	if (!(env = env_get(e)))
		return (EXIT_FAILURE);
	fstat(0, &st);
	if (S_ISCHR(st.st_mode))
	{
		//g_hst = hst_get();
		minishell(env, true);
		//hst_free(g_hst);
	}
	else
	{
		minishell(env, false);
	}
	return (EXIT_SUCCESS);
}

void sighandler(int sig)
{
	signal(sig, SIG_IGN);
}
