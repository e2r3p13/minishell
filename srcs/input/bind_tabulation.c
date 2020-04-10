/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_tabulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 11:32:46 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/10 12:23:57 by lfalkau          ###   ########.fr       */
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

static char	*find_match(DIR *dir, char *word)
{
	int				occur;
	struct dirent	*ent;
	char			*match;

	occur = 0;
	while ((ent = readdir(dir)))
	{
		if (!ft_strncmp(word, ent->d_name, ft_strlen(word)) &&
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

static char	*find_all_matches(DIR *dir, char *word)
{
	struct dirent	*ent;
	char			*match;
	char			*tmp;

	match = NULL;
	while ((ent = readdir(dir)))
	{
		if (!ft_strncmp(word, ent->d_name, ft_strlen(word) - 1) &&
			*ent->d_name != '.')
		{
			if (!(tmp = ft_strcjoin(match, ent->d_name, ' ')))
				return (match);
			if (match)
				free(match);
			match = tmp;
		}
	}
	return (match);
}

static void	autocomplete(t_dynstr *cmd, char *match, char *word, size_t *pos)
{
	size_t	wlen;
	char	*tmp;

	wlen = ft_strlen(word);
	move_cursor(left, wlen);
	writen(' ', wlen);
	move_cursor(left, wlen);
	while (wlen--)
		dynstr_pop(cmd);
	if ((tmp = ft_strjoin(cmd->str, match)))
	{
		free(cmd->str);
		cmd->str = tmp;
		cmd->len += ft_strlen(match);
		*pos = cmd->len;
		cmd->capacity = cmd->len;
		write(1, match, ft_strlen(match));
	}
	free(match);
	return ;
}

static char		*find_path(char **word)
{
	char	*path;
	char	*tmp;

	if ((tmp = ft_strrchr(*word, '/')))
	{
		if (tmp == *word)
			path = ft_strdup("/");
		else
			path = ft_strndup(*word, ft_strlen(*word) - ft_strlen(tmp));
		*word = tmp + 1;
		return (path);
	}
	return (ft_strdup("./"));
}

static char	*get_word(t_dynstr *cmd, size_t *pos)
{
	char	*word;
	char	*tmp;

	if (*pos != cmd->len)
		return (NULL);
	word = cmd->str;
	if ((tmp = ft_strrchr(word, ' ')))
		word = tmp + 1;
	return (word);
}

int			handle_tab(char *buf, size_t *pos, t_dynstr *cmd)
{
	char	*word;
	char	*path;
	char	*match;
	DIR		*dir;

	match = NULL;
	buf = NULL;
	if (!(word = get_word(cmd, pos)))
		return (0);
	if ((path = find_path(&word)))
	{
		if ((dir = opendir(path)) && *pos > 0)
		{
			match = cmd->str[*pos - 1] == '*' ?
				find_all_matches(dir, word) : find_match(dir, word);
			if (match)
				autocomplete(cmd, match, word, pos);
			closedir(dir);
		}
		free(path);
	}
	return (0);
}
