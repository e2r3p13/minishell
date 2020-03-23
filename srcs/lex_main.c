#include "libft.h"
#include "tokens.h"
#include "minishell.h"
#include <stdlib.h>

void	*g_ascii_tokens[256] =
{
	['<'] = lex_redirect,
	['>'] = lex_redirect,
	['|'] = lex_redirect,
	[';'] = lex_newline,
	['\n'] = lex_newline,
	['$'] = lex_variable,
	['\''] = lex_quote,
	['\"'] = lex_quote,
};

t_lex_lst 	*lex_lstnew(void)
{
    t_lex_lst	*lst;

    if (!(lst = malloc(sizeof(t_lex_lst))))
		return (NULL);
    lst->raw = NULL;
    lst->token = 0;
    lst->next = NULL;
    return (lst);
}

t_lex_lst	*lexer(char *str)
{
	t_lex_lst	*head;
	t_lex_lst	*cur;
	int			(*f)(char *str, t_lex_lst *lst);

	head = lex_lstnew();
	cur = head;
	while (*str)
	{
		if (cur->token)
		{
			cur->next = lex_lstnew();
			cur = cur->next;
		}
		if (*str == ' ')
			str++;
		if (!(f = g_ascii_tokens[(int)*str]))
			f = lex_word;
		str += f(str, cur);
	}
	return (head);
}
