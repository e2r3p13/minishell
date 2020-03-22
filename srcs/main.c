/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 15:13:41 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/22 19:17:05 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Main for lexer testing

static void lex_printlst(t_lex_lst *lst)
{
	while (lst)
	{
		printf("\033[0;93mT: \033[0;00m%i, \033[0;93mR: \033[0;00m%s\n", lst->token, lst->raw);
		lst = lst->next;
	}
}

int main(int ac, char **av)
{
	char		*cmd;
	t_lex_lst	*lst;

	if (ac > 1)
	{
		cmd = av[1];
		lst = lexer(cmd);
		lex_printlst(lst);
	}
}

//Real main

// int	main(int ac, char **av, char **env)
// {
// 	av[ac] = NULL;
// 	signal(SIGINT, ctrlc_handler);
// 	signal(SIGTERM, ctrld_handler);
// 	return (minishell(env));
// }
