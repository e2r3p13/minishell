/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 12:05:06 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/12 12:43:24 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

t_als	*als_get(void)
{
	t_als	*als;
	int		fd;
	char	*raw;

	als = NULL;
	if ((fd = open_reg_file(ALIASES_PATH, O_RDONLY, 0)) != -1)
	{
		while (get_next_line(fd, &raw))
		{
			if (!is_valid_assignment(raw) || als_push(&als, raw) == EXIT_FAILURE)
				break ;
		}
		free(raw);
		close(fd);
		return (als);
	}
	return (NULL);
}

int		als_push(t_als **als, char *raw)
{
	t_als	*new;

	if (!(new = malloc(sizeof(t_als))))
		return (EXIT_FAILURE);
	if (!(new->value = ft_strdup(ft_strchr(raw, '=') + 1)))
	{
		free(new);
		return (EXIT_FAILURE);
	}
	if (!(new->key = ft_strndup(raw, ft_strlen(raw) - ft_strlen(new->value) - 1)))
	{
		free(new->value);
		free(new);
	}
	new->next = *als;
	*als = new;
	free(raw);
	return (EXIT_SUCCESS);
}

void	als_print(t_als *als)
{
	while(als)
	{
		printf("key: |%s|, value: |%s|\n", als->key, als->value);
		als = als->next;
	}
}
