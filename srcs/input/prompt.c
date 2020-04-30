/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:38:04 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/30 16:46:55 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

extern int	g_exitcode;

/*
** Print the current working directory path, followed by a colored '>>'
** The color code of '>>' gives us details for the git status of the cwd
** If the script is deleted or can't be opened, '>>' will be of the same color
** than the printed path.
*/

static void	prompt_path(t_env *env)
{
	char	*pwd;
	char	*tmp;
	char	*hd;

	pwd = getcwd(NULL, 0);
	hd = get_env_var("HOME", env);
	if (pwd && hd)
	{
		if (ft_strncmp(pwd, hd, ft_strlen(hd)) == 0)
		{
			tmp = pwd;
			pwd = ft_strjoin("~", pwd + ft_strlen(hd));
			write(1, pwd, ft_strlen(pwd));
			free(pwd);
			free(tmp);
		}
		else
			write(1, pwd, ft_strlen(pwd));
	}
	if (pwd && !hd)
		write(1, pwd, ft_strlen(pwd));
}

void prompt(t_env *env)
{
	g_exitcode ? write(1, "\033[91m", 5) : write(1, "\033[92m", 5);
	prompt_path(env);
	write(1, " >\033[0m ", 7);
}
