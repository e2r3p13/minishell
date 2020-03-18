/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:37:37 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/18 20:24:36 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell(char **env)
{
	char	*cmd_line;

	while (1)
	{
		prompt(env);
		cmd_line = get_cmd();
		//TODO: parse cmd and throw syntax errors if needed
		save_cmd(cmd_line, HISTORY_PATH);
		//TODO: process cmd
		free(cmd_line);
	}
	return (0);
}

char *get_cmd()
{
	t_cmd *cmd;

	cmd = new_cmd();
	return (cmd->raw);
}
