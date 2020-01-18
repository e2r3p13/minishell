/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:38:04 by lfalkau           #+#    #+#             */
/*   Updated: 2020/01/18 19:43:47 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*g_execve_av[2] = {GDD_PATH, NULL};

static char	*get_exec_full_path(char *exec_path)
{
	char	*cwd;
	char	*path;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	tmp = ft_strjoin(cwd, "/");
	path = ft_strjoin(tmp, exec_path);
	free(tmp);
	free(cwd);
	return (path);
}

static void	prompt_git(char **env, char *exec_path)
{
	char	*exec_full_path;

	exec_full_path = get_exec_full_path(exec_path);
	execve(g_execve_av[0], g_execve_av, env);
	free(exec_full_path);
}

static void	prompt_path(char **env)
{
	char	*pwd;
	char	*hd;

	pwd = get_env_var("PWD=", env);
	hd = get_env_var("HOME=", env);
	write(0, "\033[91m", ft_strlen("\033[91m"));
	if (pwd && hd)
	{
		if (ft_strncmp(pwd, hd, ft_strlen(hd)) == 0)
		{
			pwd = ft_strjoin("~", pwd + ft_strlen(hd));
			write(0, pwd, ft_strlen(pwd));
			free(pwd);
		}
		else
			write(0, pwd, ft_strlen(pwd));
	}
	if (pwd && !hd)
		write(0, pwd, ft_strlen(pwd));
}

void		prompt(char **env, char *exec_path)
{
	pid_t pid;

	prompt_path(env);
	pid = fork();
	if (pid == 0)
	{
		prompt_git(env, exec_path);
		exit(0);
	}
	else if (pid > 0)
	{
		wait(0);
	}
	write(0, PROMPT, ft_strlen(PROMPT));
}
