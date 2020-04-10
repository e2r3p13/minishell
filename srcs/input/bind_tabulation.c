/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_tabulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 11:32:46 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/10 10:03:05 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

/*
** Following functions are used to handle autocompletion
** If the user press TAB_KEY and the cursor is at the end of the command,
** the last typed word will be completed if there is a matching file
** If there is not OR there are several, last word will not be completed
*/

static char	*find_cmp(t_dynstr *cmd, size_t *size, size_t *pos)
{
	char	*cmp;
	char	*tmp;

	if (*pos != cmd->len)
		return (NULL);
	cmp = cmd->str;
	if ((tmp = ft_strrchr(cmp, ' ')))
		cmp = tmp + 1;
	*size = ft_strlen(cmp);
	return (cmp);
}

char		*find_path(char **cmp)
{
	char	*path;
	char	*tmp;

	if ((tmp = ft_strrchr(*cmp, '/')))
	{
		if (tmp == *cmp)
			path = ft_strdup("/");
		else
			path = ft_strndup(*cmp, ft_strlen(*cmp) - ft_strlen(tmp));
		*cmp = tmp + 1;
		return (path);
	}
	return (ft_strdup("./"));
}

static char	*find_match(DIR *dir, char *cmp)
{
	int				occur;
	struct dirent	*ent;
	char			*match;

	occur = 0;
	while ((ent = readdir(dir)))
	{
		if (!ft_strncmp(cmp, ent->d_name, ft_strlen(cmp)) && *ent->d_name != 46)
		{
			if (occur < 1)
			{
				if (!(match = ft_strdup(ent->d_name)))
					return (NULL);
				if (ent->d_type == DT_DIR)
					match = ft_strpush(match, '\\');
				occur++;
			}
			else
			{
				free(match);
				return (NULL);
			}
		}
	}
	return (occur != 1 ? NULL : match);
}

void		autocomplete(t_dynstr *cmd, char *mch, char *cmp, size_t *pos)
{
	size_t	clen;
	char	*tmp;

	clen = ft_strlen(cmp);
	move_cursor(left, clen);
	writen(' ', clen);
	move_cursor(left, clen);
	while (clen--)
		dynstr_pop(cmd);
	if ((tmp = ft_strjoin(cmd->str, mch)))
	{
		free(cmd->str);
		cmd->str = tmp;
		cmd->len += ft_strlen(mch);
		*pos = cmd->len;
		cmd->capacity = cmd->len;
		write(1, mch, ft_strlen(mch));
	}
	free(mch);
	return ;
}

int			handle_tab(char *buf, size_t *pos, t_dynstr *cmd)
{
	char	*cmp;
	char	*mch;
	char	*pth;
	size_t	csiz;
	DIR		*dir;

	mch = NULL;
	buf = NULL;
	if (!(cmp = find_cmp(cmd, &csiz, pos)))
		return (0);
	if (ft_strchr(cmp, '*'))
		expand_wildcard_ft(mch, cmp, cmd, pos);
	if ((pth = find_path(&cmp)))
	{
		if ((dir = opendir(pth)))
		{
			if ((mch = find_match(dir, cmp)))
				autocomplete(cmd, mch, cmp, pos);
			closedir(dir);
		}
		free(pth);
	}
	return (0);
}
