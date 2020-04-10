/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_tabulation_0.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 11:32:46 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/10 16:20:29 by lfalkau          ###   ########.fr       */
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
}

static char	*find_path(char **word)
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
	t_ent	*e;

	match = NULL;
	buf = NULL;
	e = NULL;
	if (!(word = get_word(cmd, pos)))
		return (0);
	if ((path = find_path(&word)))
	{
		if ((dir = opendir(path)) && *pos > 0)
		{
			match = cmd->str[*pos - 1] == '*' ?
				find_all_matches(dir, word, path, e) : find_match(dir, word, e);
			if (match)
				autocomplete(cmd, match, word, pos);
			closedir(dir);
		}
		free(path);
	}
	return (0);
}
