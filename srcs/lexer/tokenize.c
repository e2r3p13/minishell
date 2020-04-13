/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 13:49:03 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/13 21:18:30 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"

int	lxr_newline(char *str, t_lxr *cur)
{
	cur->token = NEWLINE;
	if (!(cur->raw = ft_strndup(str, 1)))
		return (0);
	return (1);
}

int	lxr_redirect(char *str, t_lxr *cur)
{
	int	len;

	len = 1;
	if (*str == '>' && *(str + 1) == '>')
		len = 2;
	cur->token = REDIRECT;
	if (!(cur->raw = ft_strndup(str, len)))
		return (0);
	return (len);
}

int	lxr_quote(char *str, t_lxr *cur)
{
	int		len;
	char	*cq;

	len = 1;
	if ((cq = ft_strchr(str + 1, *str)))
		len = cq - str + 1;
	if (!(cur->raw = ft_strndup(str, len)))
		return (0);
	cur->token = *str == '"' ? DQUOTE : SQUOTE;
	return (len);
}

int	lxr_word(char *str, t_lxr *cur)
{
	int	i;

	i = 0;
	cur->token = WORD;
	while (str[i] && !ft_isinset("$<>|;\n\'\" ", str[i]))
	{
		if (str[i] == '*')
			cur->token = WILDCARD;
		i++;
	}
	if (!(cur->raw = ft_strndup(str, i)))
		return (0);
	return (i);
}

int	lxr_variable(char *str, t_lxr *cur)
{
	int	i;

	if (str[1] == '?')
	{
		cur->token = EXITCODE;
		if (!(cur->raw = ft_strdup("$?")))
			return (0);
		return (2);
	}
	if (str[1] && !ft_isalnum(str[1]) && str[1] != '_')
		return (lxr_word(str, cur));
	i = 1;
	while (str[i] == '_' || ft_isalnum(str[i]))
		i++;
	cur->token = VARIABLE;
	if (!(cur->raw = ft_strndup(str, i)))
		return (0);
	return (i);
}
