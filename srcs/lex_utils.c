#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

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

/*char	*ft_append(char *str, char c)
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
		{
			s[i] = str[i];
			i++;
		}
		free(str);
	}
	s[i++] = c;
	s[i] = 0;
	return (s);
}
*/
char    *ft_strndup(const char *s1, size_t n)
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
