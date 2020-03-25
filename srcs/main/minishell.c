/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:37:37 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/26 00:48:53 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "keys.h"
#include "tokens.h"

struct termios	g_ogterm;

int	minishell(char **env)
{
	char		*cmd;
	char		**av;
	t_lex_lst	*lxl;

	// We don't want our shell to exit unless specific cases
	while (true)
	{
		// Here we ask user to type a command and hit enter
		prompt(env);
		enable_raw_mode();
		cmd = get_cmd();
		write(1, "\n", 1);
		// We save that command to the history file
		save_cmd(cmd, HISTORY_PATH);
		// Now we turn the command line into a lexed list
		// The lexer should free cmd
		lxl = lexer(cmd);
		expand(lxl, env);
		// Lex to args doesn't free the lexer tree cause they refer to same heap
		av = lex_to_args(lxl);
		// Here we have to parse
		// Note that its the parser's responsability to free the lexed list after use
		// Then we exectute our parsed command with pipes etc
		execute(av, env);
		free(cmd);
	}
	return (0);
}

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
