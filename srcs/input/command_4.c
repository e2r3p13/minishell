/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 11:32:46 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/30 13:35:39 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

// Following functions are used to handle autocompletion
// If the user press TAB_KEY and the cursor is at the end of the command,
// the last typed word will be completed if there is a matching file
// If there is not OR there are several, last word will not be completed

static char *find_cmp(t_cmd *cmd, size_t *size)
{
	char	*cmp;
	char	*tmp;

	if (cmd->pos != cmd->len || cmd->len == 0)
		return (NULL);
	cmp = cmd->raw;
	if ((tmp = ft_strrchr(cmp, ' ')))
		cmp = tmp + 1;
	*size = ft_strlen(cmp);
	return (cmp);
}

static char *find_path(char **cmp)
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

static char *find_match(DIR *dir, char *cmp)
{
	int				occur;
	struct dirent	*ent;
	char			*match;

	if (!dir)
		return (NULL);
	occur = 0;
	while ((ent = readdir(dir)))
	{
		if (ft_strncmp(cmp, ent->d_name, ft_strlen(cmp)) == 0)
		{
			if (occur > 0)
				free (match);
			else
			{
				if (!(match = ft_strdup(ent->d_name)))
					return (NULL);
				if (ent->d_type == DT_DIR)
					match = append_backslash(match);
				occur++;
			}
		}
	}
	closedir(dir);
	return (occur > 1 ? NULL : match);
}

static void	modify_cmd(t_cmd *cmd, char *mch, char *cmp)
{
	size_t	clen;
	char	*tmp;

	clen = ft_strlen(cmp);
	term_move_cursor(left, clen);
	term_writen(' ', clen);
	term_move_cursor(left, clen);
	while (clen--)
		cmd_pop_char(cmd);
	if ((tmp = ft_strjoin(cmd->raw, mch)))
	{
		free(cmd->raw);
		cmd->raw = tmp;
		cmd->len += ft_strlen(mch);
		cmd->pos = cmd->len;
		cmd->capacity = cmd->len;
		write(1, mch, ft_strlen(mch));
	}
	return ;
}

void	cmd_handle_tab(t_cmd *cmd)
{
	char			*cmp;
	char			*mch;
	char			*pth;
	size_t			csiz;

	mch = NULL;
	if (!(cmp = find_cmp(cmd, & csiz)))
		return ;
	if ((pth = find_path(&cmp)))
	{
		mch = find_match(opendir(pth), cmp);
		if (mch != NULL)
			modify_cmd(cmd, mch, cmp);
		free(pth);
		free(mch);
	}
}