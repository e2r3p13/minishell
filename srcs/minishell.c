/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:37:37 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/25 13:23:53 by lfalkau          ###   ########.fr       */
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

// printf("\n\033[0;95mcmd: \033[0;00m%s\n", cmd);
// lex_printlst(lst);

t_lex_lst	*tkn_dup(t_lex_lst **head, int token)
{
	t_lex_lst	*n_head;
	t_lex_lst	*cur;

	n_head = lex_lstnew();
	n_head->raw = (*head)->raw;
	n_head->token = (*head)->token;
	cur = n_head;
	*head = (*head)->next;
	while (*head && (*head)->token != token)
	{
		cur->next = lex_lstnew();
		cur = cur->next;
		cur->raw = (*head)->raw;
		cur->token = (*head)->token;
		*head = (*head)->next;
	}
	return (n_head);
}


t_lex_lst	**split_tkn_lst(t_lex_lst *head)
{
	t_lex_lst	*cur;
	t_lex_lst	**sp;
	int		i;
	int		j;

	cur = head;
	i = 1;
	while (cur)
	{
		if (cur->token == NEWLINE)
			i++;
		cur = cur->next;
	}
	sp = (t_lex_lst **)malloc(sizeof(t_lex_lst *) * i + 1);
	cur = head;
	j = 0;
	while (j < i)
	{
		sp[j++] = tkn_dup(&cur, NEWLINE);
		if (cur->token == NEWLINE)
			cur = cur->next;
	}
	sp[j] = NULL;
	return (sp);
}


int	minishell(char **env)
{
	char		*cmd;
	char		**av;
	t_lex_lst	**tkn_lst;
	t_rdct		*head;

	while (true)
	{
		prompt(env);
		cmd = get_cmd();
		write(1, "\n", 1);
		save_cmd(cmd, HISTORY_PATH);
		av = lex_to_args(lexer(cmd));
		execute(av, env);
		tkn_lst = split_tkn_lst(lexer(cmd));
		while (*tkn_lst)
		{	*tkn_lst = mini_parse(*tkn_lst);
			head = parser(*tkn_lst);
			tkn_lst++;
			printf("type first tree node : %d\n", head->type);
		}
		free(cmd);
	}
	return (0);
}
