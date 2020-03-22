#include "minishell.h"
#include "libft.h"
#include "tokens.h"

int	lex_redirect(char *str, t_lex_lst *cur)
{
        int     len;

        len = 1;
        if (str[len] && ft_isinset("<>|", str[len]))
                len++;
        cur->token = REDIRECT;
        cur->raw = ft_strndup(str, len + 1);
        return (len);
}

int	lex_comment(char *str, t_lex_lst *cur)
{
        int     len;

        len = 0;
        while (str[len] && str[len] != 10)//add carriage ret?
                len++;
        cur->token = COMMENT;
        cur->raw = ft_strndup(str, len + 1);
        return (len);
}

int	lex_word(char *str, t_lex_lst **cur)
{
    int	i;

    i = 0;
    while (str[i] && ft_isalnum(str[i]))
		i++;
    (*cur)->token = WORD;
    (*cur)->raw = ft_strndup(str, i + 1);
    return (i);
}

int	lex_var(char *str, t_lex_lst **cur)
{
    int	i;

    i = 1;
    if (str[i] == '(')
        while (str[i] && str[i] != ')')
            i++;
    else
        while (str[i] && ft_isalnum(str[i]))
                    i++;
    (*cur)->token = VAR;
    (*cur)->raw = ft_strndup(str, i + 1);
    return (i);
}

int	lex_operator(char *str, t_lex_lst *cur)
{
    int	i;

    i = 0;
    while (ft_isinset("+-/*=%!", *str++))
            i++;
    cur->token = OPERATOR;
    cur->raw = ft_strndup(str, i + 1);
    return (i);
}
