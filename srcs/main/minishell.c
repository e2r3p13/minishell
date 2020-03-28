/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:37:37 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/28 23:16:08 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "keys.h"
#include "tokens.h"

struct termios	g_ogterm;

int	minishell(char **env)
{
	t_cmd		*cmd;
	char		**av;
	t_lex_lst	*lxl;
	t_hst		*hst;

	hst = hst_get();
	// We don't want our shell to exit unless specific cases
	while (true)
	{
		// Input
		prompt(env);
		term_enable_raw_mode();
		cmd = cmd_get(&hst);
		write(1, "\n", 1);
		//Lexer
		lxl = lexer(cmd->raw);
		expand(lxl, env);
		av = lex_to_args(lxl);
		//Parser
		//Execution
		execute(av, env);
		if (ft_strlen(cmd->raw) == 0)
			hst_pop_cmd(&hst);
	}
	return (0);
}

// void	print_hst(t_hst *hst)
// {
// 	while(hst)
// 	{
// 		printf("%s\n", hst->tcmd);
// 		hst = hst->prev;
// 	}
// }

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
//  	char		*cmd;
//  	t_lex_lst	**tkn_lst;
//  	t_rdct		*head;
// 	int		i;
//
//  	while (true)
//  	{
//  		prompt(env);
// 		enable_raw_mode();
//  		cmd = get_cmd();
//  		write(1, "\n", 1);
//  		save_cmd(cmd, HISTORY_PATH);
//  		tkn_lst = split_tkn_lst(lexer(cmd));
// 		i = 0;
//  		while (tkn_lst[i])
//  		{
// 			expand(tkn_lst[i], env);
//  			head = parser(tkn_lst[i]);
// 			tree_exec(head, env);
// 			free(tkn_lst[i]);
//  			i++;
//  		}
// 		free(tkn_lst);
// //		tree_free(head);
//  		free(cmd);
//  	}
//  	return (0);
// }
