#include "minishell.h"
#include "tokens.h"
#include "libft.h"

static int      lex_anti_quote(char *str, t_list *cur)
{
        int     i;

        i = 1;
        while (str[i] && ft_isalnum(str[i]))
                i++;
        cur->token = QUOTED;
        cur->raw = ft_strndup(str, i);
        return (i);
}

static int      lex_single_quote(char *str, t_list *cur)
{
        int     len;

        len = ft_strchr(str + 1, 39) - str;
        if (len > 0 && (ft_strchr(str + 1, 39) < ft_strchr(str + 1, 10)))//lacks EOT
                cur->raw = ft_strndup(str, len);
        else
        {
		ft_putstr("yo why you no found\n");
                len = 1;
                while (str[len] && str[len] != 4 && str[len] != 39)
                        len++;
                cur->raw = ft_strndup(str, len);
        }
        cur->token = QUOTED;
        return (len);
}

static int      lex_double_quote(char *str, t_list **cur)
{
        int     len;
        int     i;

        len = ft_strchr(str + 1, '"') - str;
        if (len > 0 && (ft_strchr(str + 1, '"') < ft_strchr(str + 1, 10)))
                (*cur)->raw = ft_strndup(str, len);
        else
        {
                len = 1;
                while (str[len] && str[len] != 4 && str[len] != '"')
                        len++;
                (*cur)->raw = ft_strndup(str, len);
        }
        (*cur)->token = QUOTED;
        i = ft_strchr(str, '$') - str;
        while (i > 0 && i < len)//euh... not so sure
        {
                (*cur)->next = ft_list_new(NULL);
                *cur = (*cur)->next;
                i += lex_var(str + i, cur);
                i += ft_strchr(str + i, '$') - str;
        }
        return (len);
}

int      lex_quoted(char *str, t_list **cur)
{
        int     i;

        i = 0;
        if (*str == 39)
                return (lex_single_quote(str, *cur));
        else if (*str == '"')
                return (lex_double_quote(str, cur));
        else if (*str == 92)
                return (lex_anti_quote(str, *cur));
        return (i);
}
