/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:38:04 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/28 22:36:59 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"

char	*g_execve_av[2] = {GDD_PATH, NULL};

// Print the current working directory path, followed by a colored '>>'
// The color code of '>>' gives us details for the git status of the cwd
// If the script is deleted or can't be opened, '>>' will be of the same color
// than the printed path.

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

void		prompt(char **env)
{
	int pid;

	prompt_path(env);
	pid = fork();
	if (pid == 0)
	{
		execve(g_execve_av[0], g_execve_av, env);
		// Simple git prompt if execve fails
		write(1, " » \033[0;00m", 11);
		exit(0);
	}
	else if (pid > 0)
		wait(0);
	else
		write(1, "\033[0;00m", 7);
}
