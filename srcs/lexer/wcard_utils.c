#include "minishell.h"
#include <stdlib.h>

int	wd_mch(char *s1, char *s2)
{
	if (*s2 == 0)
		return (*s1 == 0);
	while (*s2 == '*' && *(s2 + 1) == '*')
		s2++;
	if (*s1 == 0 && *s2 == '*')
		return (wd_mch(s1, s2 + 1));
	if (*s1 == *s2)
		return (wd_mch(s1 + 1, s2 + 1));
	if (*s1 != *s2)
		return ((*s2 == '*') ? (wd_mch(s1 + 1, s2) || wd_mch(s1, s2 + 1)) : 0);
	return (1);                                                        
}

int	match_nb(DIR *dir, char *s, char *pth)
{
	struct dirent		*ent;
	int			i;
	char			*tmp;

	i = 0;
	while ((ent = readdir(dir)))
	{
		if (ft_strncmp(pth, "./", 3))
			tmp = ft_strjoin(pth, ent->d_name);
		else
			tmp = ft_strdup(ent->d_name);
		if (*(ent->d_name) != '.' && wd_mch(tmp, s))
			i++;
		free(tmp);
	}
	return (i);
}
