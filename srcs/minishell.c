/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:37:37 by lfalkau           #+#    #+#             */
/*   Updated: 2020/01/21 02:57:13 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell(char **env, char *exec_path)
{
	char	*line;

	prompt(env, exec_path);
	while (get_next_line(0, &line))
	{
		prompt(env, exec_path);
		chdir(line);
		save_command(line, "/tmp/history");
		free(line);
	}
	free(line);
	return (0);
}
