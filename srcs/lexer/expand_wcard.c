/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wcard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 21:05:56 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/10 17:36:09 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"
#include <stdlib.h>

static void	find_wildcard_match(DIR *dir, char *s, char **tab, char *pth)
{
	struct dirent	*ent;
	char			*tmp;
	int				i;

	i = 0;
	while ((ent = readdir(dir)))
	{
		if (ft_strncmp(pth, "./", 3))
			tmp = ft_strjoin(pth, ent->d_name);
		else
			tmp = ft_strdup(ent->d_name);
		if (*(ent->d_name) != '.' && wd_mch(tmp, s))
			tab[i++] = ft_strdup(tmp);
		free(tmp);
	}
	tab[i] = NULL;
}

static char	*check_slash(char *pth)
{
	if (pth[ft_strlen(pth) - 1] == '/')
		return (ft_strdup(pth));
	else
		return (ft_strjoin(pth, "/"));
}

static char	**match_wildcard(char *s)
{
	char	**tab;
	char	*pth;
	DIR		*dir;
	char	*tmp;

	tmp = s;
	if (!(pth = find_path(&tmp)))
		return (NULL);
	if (!(dir = opendir(pth)))
		return (NULL);
	if (!(tmp = check_slash(pth)))
		return (NULL);
	if (!(tab = malloc(sizeof(char *) * (match_nb(dir, s, tmp) + 1))))
		return (NULL);
	closedir(dir);
	dir = opendir(pth);
	find_wildcard_match(dir, s, tab, tmp);
	free(pth);
	free(tmp);
	closedir(dir);
	return (tab);
}

char		*wildcard_to_str(char *str)
{
	char	**tab;
	char	*s1;
	char	*tmp;
	int		i;

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

int			expand_wcard(t_lxr **head, t_lxr *cur)
{
	int		i;
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
			lxr_append(&cur);
	}
	cur->next = save;
	*head = cur;
	ft_free_array(tab);
	return (EXIT_SUCCESS);
}
