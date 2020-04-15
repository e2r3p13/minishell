/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_tabulation_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 16:12:00 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/15 17:50:08 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

char	*find_match(DIR *dir, char *word, t_ent *ent)
{
	int				occur;
	char			*match;

	occur = 0;
	while ((ent = readdir(dir)))
	{
		if (!ft_strncmp_wc(word, ent->d_name, ft_strlen(word)) &&
			*ent->d_name != '.')
		{
			if (occur)
			{
				free(match);
				return (NULL);
			}
			if (!(match = ft_strdup(ent->d_name)))
				return (NULL);
			if (ent->d_type == DT_DIR)
				match = ft_strpush(match, '/');
			occur++;
		}
	}
	return (occur != 1 ? NULL : match);
}

char	*find_all_matches(DIR *dir, char *word, char *path, t_ent *ent)
{
	char			*match;
	char			*tmp;
	char			*tmp2;

	match = NULL;
	tmp2 = NULL;
	while ((ent = readdir(dir)))
	{
		if (!ft_strncmp(word, ent->d_name, ft_strlen(word) - 1) &&
			*ent->d_name != '.')
		{
			if (match && ft_strcmp(path, "./") &&
				!(tmp2 = ft_strcjoin(path, ent->d_name, '/')))
				return (match);
			if (!(tmp = tmp2 ? ft_strcjoin(match, tmp2, ' ') :
				ft_strcjoin(match, ent->d_name, ' ')))
				return (match);
			if (tmp2)
				free(tmp2);
			if (match)
				free(match);
			match = tmp;
		}
	}
	return (match);
}
