/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 15:13:41 by lfalkau           #+#    #+#             */
/*   Updated: 2020/01/16 17:36:17 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"
#include "libft.h"

int main(int ac, char **av, char **env)
{
	av[ac] = NULL;
	return (minishell(env));
}

int	minishell(char **env)
{
	char	*line;

	prompt(env);
	while (get_next_line(0, &line))
	{
		prompt(env);
		free(line);
	}
	free(line);
	return (0);
}

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
