#include "libft.h"
#include "tokens.h"
#include "minishell.h"

int	lex_var(char *str, t_list **cur)
{
	int	i;

	i = 1;
	ft_putstr("in get_var\n");
	while (str[i] && ft_isalnum(str[i]))
		i++;
	(*cur)->token = VAR;
	(*cur)->raw = ft_strndup(str, i + 1);
	return (i);
}

static int	get_word(char *str, t_list **cur)
{
	int	i;

	i = 0;
	ft_putstr("in get_word :\t");
	while (str[i] && ft_isalnum(str[i]))
		i++;
	(*cur)->token = WORD;
	(*cur)->raw = ft_strndup(str, i + 1);
	return (i);
}

static int	get_comment(char *str, t_list *cur)
{
	int	len;

	len = 0;
	ft_putstr("in get_comment :\t");
	while (str[len] && str[len] != 10)//add carriage ret?
		len++;
	cur->token = COMMENT;
	cur->raw = ft_strndup(str, len + 1);
	return (len);
}

t_list		*lexer(char *str)
{
	t_list	*head;
	t_list	*cur;
	int	i;

	head = ft_list_new(NULL);
	cur = head;
	i = 0;
	while (str[i])
	{
//		ft_putstr("top while\n");
		if (cur->token)
		{
			cur->next = ft_list_new(NULL);
			cur = cur->next;
		}
		ft_putchar(str[i]);
		if (str[i] == ' ')
			i++;
		else if (str[i] == 4)//might not be necessary
			cur->token = EOI;
		else if (str[i] == '\n' || str[i] == ';')
			cur->token = NEWLINE;
		else if (ft_isinset("+-*/%=!", str[i]) && cur->token != OPERATOR)
			cur->token = OPERATOR;
		else if (ft_isinset("\\\'\"", str[i]))
			i += lex_quoted(str + i, &cur);
		else if (str[i] == '$')
			i += lex_var(str + i, &cur);
		else if (str[i] == '#')
			i += get_comment(str + i, cur);
		else
			i += get_word(str + i, &cur);
	}
	return (head);
}
