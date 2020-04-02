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

static int	get_match_nb(DIR *dir, char *s, char *pth)
{
	struct dirent	*ent;
	int		i;
	char		*tmp;

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

static void	find_wildcard_match(DIR *dir, char *s, char **tab, char *pth)
{
	struct dirent	*ent;
	char		*tmp;
	int		i;

	i = 0;
	while((ent = readdir(dir)))
	{
		if (ft_strncmp(pth, "./", 3))
			tmp = ft_strjoin(pth, ent->d_name);
		else
			tmp = ft_strdup(ent->d_name);
		if (*(ent->d_name) != '.' && wd_mch(tmp, s))
		{
			tab[i++] = ft_strdup(tmp);
		}
		free(tmp);
	}
	tab[i] = NULL;
}

static char	**match_wildcard(char *s)
{
	char	**tab;
	char	*pth;
	DIR	*dir;
	char	*tmp;

	tmp = s;
	if (!((pth = find_path(&tmp)) && (dir = opendir(pth))))
		return (NULL);
	tmp = (pth[ft_strlen(pth) - 1] == '/') ? ft_strjoin(pth, "") : ft_strjoin(pth, "/");
	if (!(tab = (char **)malloc(sizeof(char *) * (get_match_nb(dir, s, tmp) + 1))))
		return (NULL);
	closedir(dir);
	dir = opendir(pth);
	find_wildcard_match(dir, s, tab, tmp);
	free(pth);
	free(tmp);
	closedir(dir);
	return (tab);
}

char	*wildcard_to_str(char *str)
{
	char	**tab;
	char	*s1;
	char	*tmp;
	int	i;

	i = 0;
	s1 = NULL;
	tab = match_wildcard(str);
	if (!tab || !tab[i])
		return (ft_strdup(str));
	s1 = ft_strdup(tab[i++]);
	while (tab[i])
	{
		tmp = ft_strjoin(s1, " ");
		free(s1);
		s1 = ft_strjoin(tmp, tab[i++]);
		free(tmp);
	}
	ft_free_array(tab);
	return (s1);
}

void	expand_wildcard(t_lxr **head, t_lxr *cur)
{
	int	i;
	char	**tab;
	char	*tmp;
	t_lxr	*save;

	save = cur->next;
	tmp = wildcard_to_str(cur->raw);
	tab = ft_split(tmp, ' ');
	free(cur->raw);
	free(tmp);
	i = 0;
	while (tab[i])
	{
		cur->token = WORD;
		cur->raw = ft_strdup(tab[i++]);
		cur->space = 1;
		if (tab[i])
		{
			cur->next = lxr_lstnew();
			cur = cur->next;
		}
	}
	cur->next = save;
	*head = cur;
	ft_free_array(tab);
}
