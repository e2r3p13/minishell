#include "minishell.h"
#include "tokens.h"

char		*insert_var(char *str)
{
	int	i;
	int	j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = NULL;
	while (str[j + i])
	{
		if (str[j + i] == '$')
		{
			new_str = ft_strjoin(new_str, ft_strndup(str + j, i));
			new_str = ft_strjoin(new_str, expand(str + j + i));//<-expand ?!
			j += i;
			i = 0;
		}
		i++;
	}
	new_str = ft_strjoin(new_str, ft_strndup(str + j, i));
	return (new_str);
}

t_lex_lst	*parse_dquote(t_lex_lst *cur)
{
	if (cur->raw[0] != '"' ||
		cur->raw[ft_strlen(cur->raw) - 1] != '"')
		return (NULL);
	cur->raw = insert_var(cur->raw);
	cur->raw = ft_strndup(cur->raw + 1, ft_strlen(cur->raw) - 2);
	cur->token = WORD;
	return (cur);
}

t_lex_lst	*parse_squote(t_lex_lst *cur)
{
	if (cur->raw[0] != '"' ||
		cur->raw[ft_strlen(cur->raw) - 1] != '"')
		return (NULL);
	cur->raw = ft_strndup(cur->raw + 1, ft_strlen(cur->raw) - 2);
	cur->token = WORD;
	return (cur);
}

t_lex_lst	*parse_bslash(t_lex_lst *cur)
{
	if (ft_isinset("$\"'{}()[]\\|&;<>?*=#~% ", cur->raw[1]))//lacks tab + weird quote
		cur->raw = ft_strdup(cur->raw + 1);
	cur->token = WORD;
	return (cur);
}


t_lex_lst	*mini_parse(t_lex_lst *head)
{
	t_lex_lst	*cur;

	cur = head;
	while (cur)
	{
		if (cur->token == DQUOTE)
			cur = parse_dquote(cur);
		else if (cur->token == SQUOTE)
			cur = parse_squote(cur);
		else if (cur->token == BSLASH)
			cur = parse_bslash(cur);
		else if (cur->token == VARIABLE)
			cur = parse_variable(&cur);//<-parse_variable ?!
		if (!cur)
			return (NULL);
		cur = cur->next;
	}
	return (head);
}
