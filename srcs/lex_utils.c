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
