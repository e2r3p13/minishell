#include "libft.h"
#include "tokens.h"
#include "minishell.h"
#include <unistd.h>

static int	get_var(char *str, t_list **cur)
{
	int	i;

	i = 1;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	(*cur)->token = VAR;
	(*cur)->raw = ft_strndup(str, i);
	return (i);
}

static int	get_word(char *str, t_list **cur)
{
	int	i;

	i = 0;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	(*cur)->token = WORD;
	(*cur)->raw = ft_strndup(str, i);
	return (i);
}

static int	get_anti_quote(char *str, t_list *cur)
{
	int	i;

	i = 1;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	cur->token = QUOTED;
	cur->raw = ft_strndup(str, i);
	return (i);
}

static int	get_single_quote(char *str, t_list *cur)
{
	int	len;

	len = ft_strchr(str + 1, 39) - str;
	if (len > 0 && (ft_strchr(str + 1, 39) < ft_strchr(str + 1, 10)))//lacks EOT
		cur->raw = ft_strndup(str, len);
	else
	{
		len = 1;
		while (str[len] && str[len] != 4 && str[len] != 39)
			len++;
		cur->raw = ft_strndup(str, len);
	}
	cur->token = QUOTED;
	return (len);
}

static int	get_double_quote(char *str, t_list **cur)
{
	int	len;
	int	i;

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
		i += get_var(str + i, cur);
		i += ft_strchr(str + i, '$') - str;
	}
	return (len);
}

static int	get_quoted(char *str, t_list **cur)
{
	int	i;

	i = 0;
	if (*str == 39)
		return (get_single_quote(str, *cur));
	else if (*str == '"')
		return (get_double_quote(str, cur));
	else if (*str == 92)
		return (get_anti_quote(str, *cur));
	return (i);
}

static int	get_comment(char *str, t_list *cur)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != 10)//add carriage ret?
		len++;
	cur->token = COMMENT;
	cur->raw = ft_strndup(str, len);
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
		if (cur->token)
		{
			cur->next = ft_list_new(NULL);
			cur = cur->next;
		}
		if (str[i] == ' ')
			i++;
		else if (str[i] == 4)//might not be necessary
			cur->token = EOI;
		else if (str[i] == '\n' || str[i] == ';')
			cur->token = NEWLINE;
		else if (ft_isinset("+-*/%=!", str[i]) && cur->token != OPERATOR)
			cur->token = OPERATOR;
		else if (ft_isinset("\\\'\"", cur->raw[0]))
			i += get_quoted(str + i, &cur);
		else if (str[i] == '$')
			i += get_var(str + i, &cur);
		else if (str[i] == '#')
			i += get_comment(str + i, cur);
		else
			i += get_word(str + i, &cur);
	}
	return (head);
}
