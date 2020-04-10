/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_tabulation_0.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 11:32:46 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/10 20:48:34 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

/*
** Following functions are used to handle autocompletion
** If the user press TAB_KEY and the cursor is at the end of the command,
** the last typed word will be completed if there is a matching file
** If there is not OR there are several, last word will not be completed
*/

static void	autocomplete(t_dynstr *dstr, char *match, char *word, size_t *cpos)
{
	size_t	wlen;
	char	*tmp;

	wlen = ft_strlen(word);
	move_cursor(left, wlen);
	writen(' ', wlen);
	move_cursor(left, wlen);
	while (wlen--)
		dynstr_pop(dstr);
	if ((tmp = ft_strjoin(dstr->str, match)))
	{
		free(dstr->str);
		dstr->str = tmp;
		dstr->len += ft_strlen(match);
		*cpos = dstr->len;
		dstr->capacity = dstr->len;
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

static char	*get_word(t_dynstr *dstr, size_t *cpos)
{
	char	*word;
	char	*tmp;

	if (*cpos != dstr->len)
		return (NULL);
	word = dstr->str;
	if ((tmp = ft_strrchr(word, ' ')))
		word = tmp + 1;
	return (word);
}

int			handle_tab(t_dynstr *dstr, size_t *cpos)
{
	char	*word;
	char	*path;
	char	*match;
	DIR		*dir;
	t_ent	*e;

	match = NULL;
	e = NULL;
	if (!(word = get_word(dstr, cpos)))
		return (0);
	if ((path = find_path(&word)))
	{
		if ((dir = opendir(path)) && *cpos > 0)
		{
			match = dstr->str[*cpos - 1] == '*' ?
				find_all_matches(dir, word, path, e) : find_match(dir, word, e);
			if (match)
				autocomplete(dstr, match, word, cpos);
			closedir(dir);
		}
		free(path);
	}
	return (0);
}
