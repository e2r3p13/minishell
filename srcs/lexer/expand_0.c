/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 17:31:22 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/07 09:55:06 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"

extern int g_exitcode;

// Remove quotes and replace variables when needed
t_bool	expand(t_lxr *lst, t_env *env)
{
	t_lxr	*save;

	save = lst;
	while (lst)
	{
		if (lst->token == DQUOTE && !expand_dquotes(lst, env))
			return (failure);
		if (lst->token == SQUOTE && !expand_squotes(lst))
			return (failure);
		if (lst->token == VARIABLE)
			 lst->raw = expand_variable(lst->raw, env);
		if (lst->token == WILDCARD)
			expand_wildcard(&lst, lst);
		if (lst->token == EXITCODE)
 			lst->raw = expand_exitcode(lst->raw);
		if (lst->token != REDIRECT && lst->token != NEWLINE)
			lst->token = WORD;
		if (!lst->raw)
			return (failure);
		lst = lst->next;
	}
	if (!(join_unspaced_words(save)))
		return (failure);
	return (success);
}

// Needed to join unspaced args if needed, ex:
// 'ec"ho" cou"cou" le"s co"pains' should result in:
// '|echo| |coucou| |les copains|'
t_bool	join_unspaced_words(t_lxr *l)
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
				return (failure);
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
	return (success);
}

// Ex: '$pwd' --> '/Users/moi/Desktop/minishell'
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

// Ex: '$?' --> '0' (Using exit status of the last executed command)
char	*expand_exitcode(char *raw)
{
	char	*i;

	if (!(i = ft_itoa(g_exitcode)))
		return (NULL);
	if (raw)
		free(raw);
	return (i);
}
