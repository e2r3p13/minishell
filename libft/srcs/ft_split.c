/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 19:50:12 by lfalkau           #+#    #+#             */
/*   Updated: 2019/10/21 19:50:02 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_count_words(char const *s, char c)
{
	unsigned int nb_words;
	unsigned int i;

	if (s[0] == '\0')
		return (0);
	nb_words = (s[0] == c) ? 0 : 1;
	i = 1;
	while (s[i])
	{
		if (s[i] != c && s[i - 1] == c)
			nb_words++;
		i++;
	}
	return (nb_words);
}

static void	*ft_free(char **array, int index)
{
	while (--index >= 0)
		free(array[index]);
	free(array);
	return (NULL);
}

static int	ft_skip_n_count(char c, char **s)
{
	int i;

	while (**s && **s == c)
		(*s)++;
	i = 0;
	while ((*s)[i] && (*s)[i] != c)
		i++;
	return (i);
}

char		**ft_split(char const *s, char c)
{
	unsigned int	nb_words;
	size_t			len_word;
	char			**array;
	unsigned int	i;

	if (!s)
		return (NULL);
	nb_words = ft_count_words(s, c);
	if (!(array = (char **)malloc(sizeof(char *) * (nb_words + 1))))
		return (NULL);
	i = 0;
	while (i < nb_words)
	{
		len_word = ft_skip_n_count(c, (char **)&s);
		if (!(array[i] = (char *)malloc(sizeof(char) * (len_word + 1))))
			return (ft_free(array, i));
		ft_strlcpy(array[i], s, len_word + 1);
		s += len_word;
		i++;
	}
	array[i] = NULL;
	return (array);
}
