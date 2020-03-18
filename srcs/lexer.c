#include "libft.h"
#include "tokens.h"
#include "minishell.h"
#include <unistd.h>

static int	get_quoted(char *str, t_list *cur)
{
	int	i;

	i = 0;
	return (i);
}

static int	get_comment(char *str, t_list *cur)
{
	int	i;

	i = 0;
	return (i);
}

t_list		*lexer(char *str)
{
	t_list	*head;
	t_list	*cur;
	int	i;

	head = ft_list_new("");
	cur = head;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			if (cur->token)
			{
				cur->next = ft_list_new("");
				cur = cur->next;
			}
		}
		else if (str[i] == 4)
		{
			if (cur->token)
			{
				cur->next = ft_list_new("");
				cur = cur->next;
			}
			cur->token = EOI;
		}
		else if (str[i] == '\n' || str[i] == ';')
		{
			if (cur->token)
			{
				cur->next = ft_list_new("");
				cur = cur->next;
			}
			cur->token = NEWLINE;
		}
		else if (ft_isinset("+-*/%=!", str[i]) && cur->token != OPERATOR)
		{
			if (cur->token)
			{
				cur->next = ft_list_new("");
				cur = cur->next;
			}
			cur->token = OPERATOR;
		}
		else if (ft_isinset("\\\'\"", cur->raw[0]))
		{
/*			i += get_quoted(str + i, cur);
			while (cur->next)
				cur = cur->next;
*/			if (cur->token == QUOTED)
				cur->raw = append(cur->raw, str[i]);
			else
			{
				cur->next = ft_list_new("");
				cur = cur->next;
				cur->token = QUOTED;
			}
		}
		else if (str[i] == '$')
		{
			if (cur->token)
			{
				cur->next = ft_list_new("");
				cur = cur->next;
			}
			cur->token = VAR;
		}
		else if (str[i] == '#')
		{
//			i += get_comment(str + i, cur);
			cur->next = ft_list_new("");
			cur = cur->next;
			cur->token = COMMENT;
			while (str[i + 1] && str[i + 1] != 4 && str[i + 1] != '\n')
				cur->raw = append(cur->raw, str[i++]);
		}
		else if (!cur->token)
		{
			cur->token = WORD;
		}
		cur->raw = append(cur->raw, str[i++]);
	}
	cur = head->next;
	free(head);
	return (cur);
}
