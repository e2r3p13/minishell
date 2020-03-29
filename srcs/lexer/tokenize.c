/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 13:49:03 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/29 18:05:16 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "tokens.h"

int	lxr_newline(char *str, t_lxr *cur)
{
    cur->token = NEWLINE;
    cur->raw = ft_strndup(str, 1);
    return (1);
}

int	lxr_redirect(char *str, t_lxr *cur)
{
    int	len;

	len = 1;
    if ((*str == '<' || *str == '>') && *(str + 1) && *(str + 1) == *str)
		len = 2;
	cur->token = REDIRECT;
    cur->raw = ft_strndup(str, len);
    return (len);
}

int	lxr_quote(char *str, t_lxr *cur)
{
	int		len;
	char	*cq;

	len = 1;
	if ((cq = ft_strchr(str + 1, *str)))
		len = cq - str + 1;
	cur->raw = ft_strndup(str, len);
    cur->token = *str == '"' ? DQUOTE : SQUOTE;
    return (len);
}

int	lxr_word(char *str, t_lxr *cur)
{
    int	i;

    i = 0;
    while (str[i] && !ft_isinset("<>|;\n\'\" ", str[i]))
	{
		if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
			return (i);
		i++;
	}
    cur->token = WORD;
    cur->raw = ft_strndup(str, i);
    return (i);
}

int	lxr_variable(char *str, t_lxr *cur)
{
    int	i;

	if (str[1] == '?')
	{
		cur->token = EXITCODE;
		cur->raw = ft_strdup("$?");
	    return (2);
	}
	if (!ft_isalnum(str[1]) && str[1] != '_')
	{
		return (lxr_word(str, cur));
	}
	i = 1;
	while (str[i] == '_' || ft_isalnum(str[i]))
		i++;
	cur->token = VARIABLE;
    cur->raw = ft_strndup(str, i);
    return (i);
}
