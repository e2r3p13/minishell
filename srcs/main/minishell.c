/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:37:37 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/29 18:06:19 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "keys.h"
#include "tokens.h"

struct termios	g_ogterm;

int	minishell(char **env)
{
	t_hst	*history;
	t_cmd	*command;
	t_lxr	**lexlst;
	int		i;

	history = hst_get();
	while (true)
	{
		prompt(env);
		command = cmd_get(&history);
		write(1, "\n", 1);
		if ((lexlst = lxr_split(lexer(command->raw))))
		{
			lxr_print(lexlst);
			i = 0;
			while (lexlst[i])
			{
				expand(lexlst[i], env);
				//execute(parse(lexerlst[i]));
				lxr_free(lexlst[i]);
				i++;
			}
			free(lexlst);
			if (ft_strlen(command->raw) == 0)
				hst_pop_cmd(&history);
		}
		else
			write(1, "Invalid command\n", 16);
	}
	return (0);
}

// void	print_hst(t_hst *history)
// {
// 	while(history)
// 	{
// 		printf("%s\n", history->tcmd);
// 		history = history->prev;
// 	}
// }

// static void lex_printlst(t_lxr *lst)
// {
// 	while (lst)
// 	{
// 		printf("\033[0;93mT: \033[0;00m%i, \033[0;93mR: \033[0;00m%s\n", lst->token, lst->raw);
// 		lst = lst->next;
// 	}
// }

// printf("\n\033[0;95mcmd: \033[0;00m%s\n", command);
// lex_printlst(lst);

// int	minishell(char **env)
// {
//  	char		*command;
//  	t_lxr	**tkn_lst;
//  	t_rdct		*head;
// 	int		i;
//
//  	while (true)
//  	{
//  		prompt(env);
// 		enable_raw_mode();
//  		command = get_cmd();
//  		write(1, "\n", 1);
//  		save_cmd(command, HISTORY_PATH);
//  		tkn_lst = split_tkn_lst(lexer(command));
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
//  		free(command);
//  	}
//  	return (0);
// }
