#include "minishell.h"
#include "tokens.h"
#include "libft.h"

static int      lex_anti_quote(char *str, t_lex_lst *cur)
{
        int     i;

        i = 2;
        cur->token = QUOTED;
        cur->raw = ft_strndup(str, i + 1);
        return (i);
}

static int      lex_single_quote(char *str, t_lex_lst *cur)
{
        int     len;
	char	*c;

	c = ft_strchr(str + 1, 39);
        len = c - str + 1;
        if (len > 0)//lacks EOT
                cur->raw = ft_strndup(str, len + 1);
        else
        {
                len = 1;
                while (str[len] && str[len] != 4 && str[len] != 39)
                        len++;
                cur->raw = ft_strndup(str, len + 1);
        }
        cur->token = QUOTED;
        return (len);
}

static void	spot_var(char *s, t_lex_lst **c, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		if (s[i] == '$' || s[i] == '\\')
		{
                	(*c)->next = lex_lstnew();
                	*c = (*c)->next;
		}
		if (s[i] == '$')
                	i += lex_var(s + i, c);
		else if (s[i] == '\\')
			i += lex_anti_quote(s + i, *c);
		i++;
	}
}

static int      lex_double_quote(char *str, t_lex_lst **cur)
{
        int     len;

        len = ft_strchr(str + 1, '"') - str + 1;
        if (len > 0)
                (*cur)->raw = ft_strndup(str, len + 1);
        else
        {
                len = 1;
                while (str[len] && str[len] != 4 && str[len] != '"')
                        len++;
                (*cur)->raw = ft_strndup(str, ++len + 1);
        }
        (*cur)->token = QUOTED;
        return (len);
}

int      lex_quoted(char *str, t_lex_lst **cur)
{
        int     i;

        i = 0;
        if (*str == 39)
                i += (lex_single_quote(str, *cur));
        else if (*str == '"')
	{
                i += (lex_double_quote(str, cur));
		spot_var(str, cur, i);
	}
        else if (*str == 92)
                i += (lex_anti_quote(str, *cur));
        return (i);
}
