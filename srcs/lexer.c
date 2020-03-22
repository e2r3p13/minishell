#include "libft.h"
#include "tokens.h"
#include "minishell.h"
#include <stdlib.h>

t_list 		*ft_list_new(void)
{
        t_list *lst;

        if (!(lst = (t_list *)malloc(sizeof(t_list))))
                return (NULL);
        lst->raw = NULL;
        lst->token = 0;
        lst->next = NULL;
        return (lst);
}

char		*ft_strndup(const char *s1, size_t n)
{
        size_t  len;
        char    *s2;

        len = ft_strlen(s1);
        if (len < n)
        {
                if (!(s2 = (char *)malloc(sizeof(char) * (len + 1))))
                        return (NULL);
                ft_strlcpy(s2, s1, n + 1);
        }
        else
        {
                if (!(s2 = (char *)malloc(sizeof(char) * (n + 1))))
                        return (NULL);
                ft_strlcpy(s2, s1, n);
                s2[++n] = 0;
        }
        return (s2);
}

static void	lex(char *str, t_list *cur, int i)
{
	while (str[i])
	{
		if (cur->token)
		{
			cur->next = ft_list_new();
			cur = cur->next;
		}
		ft_putchar(str[i]);
		if (str[i] == ' ')
			i++;
		else if (str[i] == 4)//might not be necessary
			cur->token = EOI;
		else if (str[i] == '\n' || str[i] == ';')
			cur->token = NEWLINE;
		else if (ft_isinset("+-*/%=!", str[i]))
			i += lex_operator(str + i, cur);
		else if (ft_isinset("\\\'\"", str[i]))
			i += lex_quoted(str + i, &cur);
		else if (str[i] == '$')
			i += lex_var(str + i, &cur);
		else if (str[i] == '#')
			i += lex_comment(str + i, cur);
		else if (ft_isinset("<>|", str[i]))
			i += lex_redirect(str + i, cur);
		else
			i += lex_word(str + i, &cur);
	}
}

t_list		*lexer(char *str)
{
	t_list	*head;
	int	i;

	head = ft_list_new();
	i = 0;
	lex(str, head, i);
	return (head);
}
