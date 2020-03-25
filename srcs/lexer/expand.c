/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 17:31:22 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/26 00:08:53 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"

char	*expand_variable(char *raw, char **env)
{
	char *var;
	char *val;

	var = ft_strjoin(raw + 1, "=");
	val = get_env_var(var, env);
	val = val ? ft_strdup(val) : ft_strdup("");
	free(raw);
	free(var);
	raw = val;
	return (raw);
}

char	*expand_exitcode(char *raw)
{
	return (raw);
}

void	join_unspaced_words(t_lex_lst *lst)
{
	void	*tmp;

	while (lst)
	{
		if (lst->space == false && lst->next && lst->next->token == WORD)
		{
			tmp = lst->raw;
			lst->raw = ft_strjoin(tmp, lst->next->raw);
			free(tmp);
			if (lst->next)
				lst->space = lst->next->space;
			tmp = lst->next;
			lst->next = lst->next->next;
			free(tmp);
		}
		else
			lst = lst->next;
	}
}

t_bool	expand(t_lex_lst *lst, char **env)
{
	t_lex_lst	*save;

	save = lst;
	while (lst)
	{
		if (lst->token == DQUOTE && !expand_dquotes(lst, env))
			return (false);
		if (lst->token == SQUOTE && !expand_squotes(lst))
			return (false);
		if (lst->token == VARIABLE)
			 lst->raw = expand_variable(lst->raw, env);
		 if (lst->token == EXITCODE)
 			 lst->raw = expand_exitcode(lst->raw);
		lst->token = WORD;
		lst = lst->next;
	}
	join_unspaced_words(save);
	return (true);
}
