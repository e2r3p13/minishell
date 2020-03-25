/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 23:55:34 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/26 00:06:34 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"

char	*remove_quotes(char *raw)
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

t_bool	expand_squotes(t_lex_lst *lst)
{
	if (!(lst->raw = remove_quotes(lst->raw)))
		return (false);
	return (true);
}

t_bool	expand_dquotes(t_lex_lst *lst, char **env)
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
