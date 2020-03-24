/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:37:37 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/24 20:58:30 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "keys.h"

struct termios	g_ogterm;

// static void lex_printlst(t_lex_lst *lst)
// {
// 	while (lst)
// 	{
// 		printf("\033[0;93mT: \033[0;00m%i, \033[0;93mR: \033[0;00m%s\n", lst->token, lst->raw);
// 		lst = lst->next;
// 	}
// }

int	minishell(char **env)
{
	char		*cmd_line;
	t_lex_lst	*lst;

	while (true)
	{
		prompt(env);
		enable_raw_mode();
		cmd_line = get_cmd();
		write(1, "\n", 1);
		//printf("\n\033[0;95mcmd: \033[0;00m%s\n", cmd_line);
		save_cmd(cmd_line, HISTORY_PATH);
		lst = lexer(cmd_line);
		if (fork() == 0)
			get_simple_cmd(lst, env);
		else
			wait(0);
		//lex_printlst(lst);
		free(cmd_line);
	}
	return (0);
}
