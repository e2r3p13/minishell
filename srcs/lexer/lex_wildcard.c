#include "minishell.h"
#include "tokens.h"
#include "libft.h"
#include <dirent.h>

static int	wd_mch(char *s1, char *s2)
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

static int	get_match_nb(DIR *dir, char *s)
{
	struct dirent	*ent;
	int		i;

	i = 0;
	while ((ent = readdir(dir)))
	{
		if (wd_mch(ent->d_name, s))
			i++;
	}
	return (i);
}

static void	find_wildcard_match(DIR *dir, char *s, char **tab)
{
	struct dirent	*ent;
	int		i;

	i = 0;
	while((ent = readdir(dir)))
	{
		if (wd_mch(s, ent->d_name))
		{
			tab[i++] = ft_strdup(ent->d_name);
			if (ent->d_type == DT_DIR)
				tab[i - 1] = append_backslash(tab[i - 1]);
		}
	}
	tab[i] = NULL;
}

static char	**match_wildcard(char *s)
{
	char	**tab;
	char	*path;
	DIR	*dir;
	char	*tmp;

	tmp = s;
	if (!((path = find_path(&tmp)) && (dir = opendir(path))))
		return (NULL);
	if (!(tab = (char **)malloc(sizeof(char *) * (get_match_nb(dir, s) + 1))))
		return (NULL);
	closedir(dir);
	dir = opendir(path);
	find_wildcard_match(dir, s, tab);
	free(path);
	closedir(dir);
	return (tab);
}

char	*wildcard_to_str(char *str)
{
	char	**tab;
	char	*s1;
	int	i;

	i = 0;
	s1 = NULL;
	tab = match_wildcard(str);
	if (!tab[i])
		return (str);
	s1 = tab[i++];
	while (tab[i])
	{
		s1 = ft_strjoin(s1, " ");
		s1 = ft_strjoin(s1, tab[i++]);
	}
	return (s1);
}

void	expand_wildcard(t_lxr **head, t_lxr *cur)
{
	int	i;
	char	**tab;
	t_lxr	*save;
	
	printf("yoooooooo\n");
	save = cur->next;
	cur->raw = wildcard_to_str(cur->raw);
	tab = ft_split(cur->raw, ' ');
	free(cur->raw);
	i = 0;
	while (tab[i])
	{
		cur->token = WORD;
		cur->raw = tab[i++];
		cur->space = 1;
		if (tab[i])
		{
			cur->next = lxr_lstnew();
			cur = cur->next;
		}
	}
	*head = cur;
	cur->next = save;
}
