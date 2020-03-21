/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:37:37 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/21 19:10:29 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "keys.h"

int g_pid;
int g_cpid;

int	minishell(char **env)
{
	char	*cmd_line;

	while (1)
	{
		g_cpid = fork();
		if (g_cpid == 0)
		{
			g_pid = getppid();
			prompt(env);
			enable_raw_mode();
			cmd_line = get_cmd();
			printf("\n\033[0;95mcmd: \033[0;00m%s\n", cmd_line);
			//TODO: parse cmd and throw syntax errors if needed
			save_cmd(cmd_line, HISTORY_PATH);
			//TODO: process cmd
			free(cmd_line);
			exit(0);
		}
		else
		{
			wait(0);
		}
	}
	return (0);
}
