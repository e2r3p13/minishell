/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:38:04 by lfalkau           #+#    #+#             */
/*   Updated: 2020/01/17 12:34:17 by lfalkau          ###   ########.fr       */
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

static void	prompt_gits(char **env)
{
	int		git_dir;
	char	*git_path;

	if (!(git_path = ft_strjoin(get_env_var("PWD=", env), "/.git")))
		return ;
	if ((git_dir = open(git_path, O_RDONLY)) != -1)
	{
		write(0, PROMPT_GIT, ft_strlen(PROMPT_GIT));
		close(git_dir);
	}
	free(git_path);
}

void		prompt(char **env)
{
	prompt_path(env);
	prompt_gits(env);
	write(0, PROMPT, ft_strlen(PROMPT));
}
