/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 17:31:22 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/26 18:25:55 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"

extern int g_exitcode;

char	*remove_quotes(char *raw)
{
	char	len;
	char	*tmp;

	len = ft_strlen(raw);
	if (len > 1 && raw[len - 1] == *raw)
	{
		tmp = raw;
		if (!(raw = ft_strndup(tmp + 1, len - 2)))
			return (NULL);
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

char	*expand_quoted_dollar(char *raw, char *var, size_t vlen, char **env)
{
	size_t	len;
	char	*tmp_1;
	char	*tmp_2;
	char	*tmp_3;

	len = var - raw;
	if (!(tmp_1 = len > 0 ? ft_strndup(raw, len) : ft_strdup("")))
		return (NULL);
	tmp_2 = var[1] == '?' ?
		expand_exitcode(NULL) : expand_variable(ft_strndup(var, vlen), env);
	if (!tmp_2)
		return (NULL);
	if (!(tmp_3 = ft_strjoin(tmp_1, tmp_2)))
		return (NULL);
	free(tmp_1);
	free(tmp_2);
	var += (vlen);
	if (!(tmp_1 = ft_strlen(var) > 0 ? ft_strdup(var) : ft_strdup("")))
		return (NULL);
	if (!(tmp_2 = ft_strjoin(tmp_3, tmp_1)))
		return (NULL);
	free(tmp_3);
	free(tmp_1);
	free(raw);
	return (tmp_2);
}

t_bool	expand_dquotes(t_lex_lst *lst, char **env)
{
	char	*s;
	size_t	vlen;

	if (!(lst->raw = remove_quotes(lst->raw)))
		return (false);
	s = lst->raw;
	while (*s)
	{
		if (*s == '$' && (s[1] == '_' || ft_isalnum(s[1]) || *s == '$'))
		{
			vlen = 1;
			while (s[vlen] == '_' || ft_isalnum(s[vlen]))
				vlen++;
			vlen = *(s + 1) == '?' ? 2 : vlen;
			if (!(lst->raw = expand_quoted_dollar(lst->raw, s, vlen, env)))
				return (false);
			s = lst->raw;
		}
		else
			s++;
	}
	return (true);
}

char	*expand_variable(char *raw, char **env)
{
	char *var;
	char *val;

	if (!raw)
		return (NULL);
	var = ft_strjoin(raw + 1, "=");
	if (!var)
		return (NULL);
	val = get_env_var(var, env);
	val = val ? ft_strdup(val) : ft_strdup("");
	if (!val)
		return (NULL);
	free(raw);
	free(var);
	raw = val;
	return (raw);
}

char	*expand_exitcode(char *raw)
{
	char	*i;

	if (!(i = ft_itoa(g_exitcode)))
		return (NULL);
	if (raw != NULL)
		free(raw);
	return (i);
}
