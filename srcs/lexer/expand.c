/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 17:31:22 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/25 23:38:04 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"

static char	*remove_quotes(char *raw)
{
	char	len;
	char	*tmp;

	len = ft_strlen(raw);
	if (len > 1 && raw[len - 1] == *raw)
	{
		tmp = raw;
		raw = ft_strndup(tmp + 1, len - 2);
		free(tmp);
		return (raw);
	}
	write(1, "minishell: closing quote is missing", 35);
	return (NULL);
}

static char	*expand_variable(char *raw, char **env)
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

static t_bool	expand_squotes(t_lex_lst *lst)
{
	if (!(lst->raw = remove_quotes(lst->raw)))
		return (false);
	return (true);
}

static t_bool	expand_dquotes(t_lex_lst *lst, char **env)
{
	char	*s;
	char	*var;
	char	*bgn;
	char	*end;
	int		vlen;

	if (!(lst->raw = remove_quotes(lst->raw)))
		return (false);
	s = lst->raw;
	while (*s)
	{
		if (*s == '$' && (s[1] == '_' || ft_isalnum(s[1])))
		{
			var = s;
			vlen = 1;
			while (s[vlen] && (s[vlen] == '_' || ft_isalnum(s[vlen])))
				vlen++;
			var = expand_variable(ft_strndup(var, vlen), env);
			bgn = ft_strndup(lst->raw, s - lst->raw);
			end = ft_strdup(lst->raw + ft_strlen(bgn) + vlen);
			lst->raw = superjoin(bgn, var, end, lst->raw);
			s = lst->raw;
		}
		s++;
	}
	return (true);
}

static char	*expand_exitcode(char *raw)
{
	return (raw);
}

static void		join_unspaced_words(t_lex_lst *lst)
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

t_bool			expand(t_lex_lst *lst, char **env)
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
