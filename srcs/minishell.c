/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:37:37 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/23 15:26:23 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "keys.h"

int				g_pid;
int				g_cpid;
struct termios	g_ogterm;

static void lex_printlst(t_lex_lst *lst)
{
	while (lst)
	{
		printf("\033[0;93mT: \033[0;00m%i, \033[0;93mR: \033[0;00m%s\n", lst->token, lst->raw);
		lst = lst->next;
	}
}

int	minishell(char **env)
{
	char		*cmd_line;
	t_lex_lst	*lst;

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
			save_cmd(cmd_line, HISTORY_PATH);
			lst = lexer(cmd_line);
			lex_printlst(lst);
			free(cmd_line);
			exit(0);
		}
		else
			wait(0);
	}
	return (0);
}
