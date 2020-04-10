/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 17:31:22 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/10 15:13:21 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"

int		g_exitcode = 0;

int		expand(t_lxr *lst, t_env *env)
{
	t_lxr	*save;

	save = lst;
	while (lst)
	{
		if (lst->token == DQUOTE && expand_dquotes(lst, env) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (lst->token == SQUOTE && expand_squotes(lst) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (lst->token == WILDCARD && expand_wcard(&lst, lst) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (lst->token == VARIABLE)
			lst->raw = expand_variable(lst->raw, env);
		if (lst->token == EXITCODE)
			lst->raw = expand_exitcode(lst->raw);
		if (lst->token != REDIRECT && lst->token != NEWLINE)
			lst->token = WORD;
		if (!lst->raw)
			return (EXIT_FAILURE);
		lst = lst->next;
	}
	if ((join_unspaced_words(save)) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		join_unspaced_words(t_lxr *l)
{
	void	*tmp;

	while (l)
	{
		if (!l->space && l->next && l->next->token == WORD && l->token == WORD)
		{
			tmp = l->raw;
			if (!(l->raw = ft_strjoin(tmp, l->next->raw)))
			{
				free(tmp);
				return (EXIT_FAILURE);
			}
			free(tmp);
			if (l->next)
				l->space = l->next->space;
			tmp = l->next;
			l->next = l->next->next;
			free(tmp);
		}
		else
			l = l->next;
	}
	return (EXIT_SUCCESS);
}

char	*expand_variable(char *raw, t_env *env)
{
	char *val;

	if (!raw)
		return (NULL);
	val = get_env_var(raw + 1, env);
	val = val ? ft_strdup(val) : ft_strdup("");
	if (!val)
		return (NULL);
	free(raw);
	raw = val;
	return (raw);
}

char	*expand_exitcode(char *raw)
{
	char	*i;

	if (!(i = ft_itoa(g_exitcode)))
		return (NULL);
	if (raw)
		free(raw);
	return (i);
}
