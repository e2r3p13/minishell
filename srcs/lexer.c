#include "libft.h"
#include "tokens.h"
#include "minishell.h"
#include <stdlib.h>

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

static void	lex_tokenize(char *str, t_lex_lst *cur)
{
	while (*str)
	{
		if (cur->token)
		{
			cur->next = lex_lstnew();
			cur = cur->next;
		}
		if (*str == '\n' || *str == ';')
		{
			cur->token = NEWLINE;
			str++;
		}
		else if (ft_isinset("+-*/%=!", *str))
			str += lex_operator(str, cur);
		else if (ft_isinset("\\\'\"", *str))
			str += lex_quoted(str, &cur);
		else if (*str == '$')
			str += lex_var(str, &cur);
		else if (*str == '#')
			str += lex_comment(str, cur);
		else if (ft_isinset("<>|", *str))
			str += lex_redirect(str, cur);
		else
			str += lex_word(str, &cur);
	}
}

t_lex_lst	*lexer(char *str)
{
	t_lex_lst	*head;

	head = lex_lstnew();
	lex_tokenize(str, head);
	return (head);
}
