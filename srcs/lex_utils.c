#include <stdlib.h>
#include "minishell.h"

t_list	*ft_list_new(void *content)
{
	t_list *lst;

	if (!(lst = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	lst->raw = content;
	lst->token = 0;
	lst->next = NULL;
	return (lst);
}

char	*ft_append(char *str, char c)
{
	char	*s;
	int	i;

	i = 0;
	if (!str || !*str)
	{
		if (!(s = (char *)malloc(2)))
			return (NULL);
	}
	else
	{
		if (!(s = (char *)malloc(sizeof(char) * ft_strlen(str) + 1)))
			return (NULL);
		while(str[i])
			s[i] = str[i++];
		free(str);
	}
	s[i++] = c;
	s[i] = 0;
	return (s);
}
