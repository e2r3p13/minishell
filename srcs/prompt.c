/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:38:04 by lfalkau           #+#    #+#             */
/*   Updated: 2020/01/16 22:14:38 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_var(char *var_name, char **env)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(var_name);
	while (env[i])
	{
		if (ft_strncmp(var_name, env[i], len) == 0)
			return (env[i] + len);
		i++;
	}
	return (NULL);
}

void	prompt(char **env)
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
		{
			write(0, pwd, ft_strlen(pwd));
		}
	}
	if (pwd && !hd)
	{
		write(0, pwd, ft_strlen(pwd));
	}
	write(0, PROMPT, ft_strlen(PROMPT));
}
