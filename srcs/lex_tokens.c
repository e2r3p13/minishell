/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 13:49:03 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/24 14:55:26 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "tokens.h"

int	lex_newline(char *str, t_lex_lst *cur)
{
    cur->token = NEWLINE;
    cur->raw = ft_strndup(str, 1);
    return (1);
}

int	lex_redirect(char *str, t_lex_lst *cur)
{
    int	len;

	len = 1;
    if (*str == '<' || *str == '>')
	{
		if (*(str + 1) && *(str + 1) == *str)
		{
			cur->token = *str == '<' ? DLESS : DGREAT;
			len = 2;
		}
		else
		{
			cur->token = *str == '<' ? LESS : GREAT;
		}
	}
	else if (*str == '|')
	{
		cur->token = PIPE;
	}
    cur->raw = ft_strndup(str, len);
    return (len);
}

int	lex_word(char *str, t_lex_lst *cur)
{
    int	i;

    i = 0;
    while (str[i] && !ft_isinset("<>|;\n$\'\" ", str[i]))
		i++;
    cur->token = WORD;
    cur->raw = ft_strndup(str, i);
    return (i);
}

int	lex_quote(char *str, t_lex_lst *cur)
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

int	lex_variable(char *str, t_lex_lst *cur)
{
    int	i;

	if (str[1] == ' ' || str[1] == '\0')
	{
		cur->token = WORD;
	    cur->raw = ft_strdup("$");
	    return (1);
	}
	if (str[1] == '?')
	{
		cur->token = EXITCODE;
		cur->raw = ft_strdup("$?");
	    return (2);
	}
	i = 1;
	while (str[i] == '_' || ft_isalnum(str[i]))
		i++;
	cur->token = VARIABLE;
    cur->raw = ft_strndup(str, i);
    return (i);
}
