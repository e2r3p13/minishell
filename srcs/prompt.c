/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:38:04 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/21 13:47:12 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"

char	*g_execve_av[2] = {GDD_PATH, NULL};

static void	prompt_path(char **env)
{
	char	*pwd;
	char	*tmp;
	char	*hd;

	pwd = getcwd(NULL, 0);
	hd = get_env_var("HOME=", env);
	write(1, PATH_COLOR, ft_strlen(PATH_COLOR));
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

static void	prompt_git(char **env)
{
	execve(g_execve_av[0], g_execve_av, env);
}

void		prompt(char **env)
{
	pid_t	pid;

	prompt_path(env);
	pid = fork();
	if (pid == 0)
	{
		prompt_git(env);
		exit(0);
	}
	else if (pid > 0)
	{
		wait(0);
	}
}
