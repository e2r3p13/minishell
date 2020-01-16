/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:38:04 by lfalkau           #+#    #+#             */
/*   Updated: 2020/01/16 17:38:24 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(char **env)
{
	char	*pwd;
	char	*hd;

	pwd = env[PWD] + 4;
	hd = env[HOME] + 5;
	write(0, "\033[91m", ft_strlen("\033[91m"));
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
	write(0, PROMPT, ft_strlen(PROMPT));
}
