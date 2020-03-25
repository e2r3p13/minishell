/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:37:37 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/25 22:54:26 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "keys.h"
#include "tokens.h"

struct termios	g_ogterm;

// static void lex_printlst(t_lex_lst *lst)
// {
// 	while (lst)
// 	{
// 		printf("\033[0;93mT: \033[0;00m%i, \033[0;93mR: \033[0;00m%s\n", lst->token, lst->raw);
// 		lst = lst->next;
// 	}
// }

// printf("\n\033[0;95mcmd: \033[0;00m%s\n", cmd);
// lex_printlst(lst);

int	minishell(char **env)
{
	char		*cmd;
	char		**av;
	t_lex_lst	*lxl;

	while (true)
	{
		prompt(env);
		enable_raw_mode();
		cmd = get_cmd();
		write(1, "\n", 1);
		save_cmd(cmd, HISTORY_PATH);
		lxl = lexer(cmd);
		expand(lxl, env);
		av = lex_to_args(lxl);
		execute(av, env);
		free(cmd);
	}
	return (0);
}

// int	minishell(char **env)
// {
// 	char		*cmd;
// 	char		**av;
// 	t_lex_lst	**tkn_lst;
// 	t_rdct		*head;
//
// 	while (true)
// 	{
// 		prompt(env);
// 		cmd = get_cmd();
// 		write(1, "\n", 1);
// 		save_cmd(cmd, HISTORY_PATH);
// 		av = lex_to_args(lexer(cmd));
// 		execute(av, env);
// 		tkn_lst = split_tkn_lst(lexer(cmd));
// 		while (*tkn_lst)
// 		{	*tkn_lst = mini_parse(*tkn_lst);
// 			head = parser(*tkn_lst);
// 			tkn_lst++;
// 			printf("type first tree node : %d\n", head->type);
// 		}
// 		free(cmd);
// 	}
// 	return (0);
// }
