/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:38:04 by lfalkau           #+#    #+#             */
/*   Updated: 2020/01/17 16:34:36 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	git_dir(char **env)
{
	int		fd;
	int		git;
	char	*path;

	git = 0;
	if (!(path = ft_strjoin(get_env_var("PWD=", env), "/.git")))
		return (0);
	if ((fd = open(path, O_RDONLY)) != -1)
	{
		close(fd);
		git = 1;
	}
	free(path);
	return (git);
}

void		prompt(char **env)
{
	prompt_path(env);
	if (git_dir(env))
	{
		write(0, PROMPT_GIT, ft_strlen(PROMPT_GIT));
	}
	write(0, PROMPT, ft_strlen(PROMPT));
}
