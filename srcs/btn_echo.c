/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btn_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 16:44:50 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/24 18:00:53 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static size_t	ft_strlen(char *s)
{
	int l;

	l = 0;
	while (*s++)
		l++;
	return (l);
}

static int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned long i;

	i = 0;
	while (s1[i] && s2[i] && i < n && s1[i] == s2[i])
		i++;
	return (i == n ? 0 : ((unsigned char)s1[i] - (unsigned char)s2[i]));
}

static int		set_flag(char *arg, int *f)
{
	arg++;

	while (*arg)
	{
		if (*arg == 'n')
			*f |= 0b1000;
		else
			return (0);
		arg++;
	}
	return (1);
}

int				main(int ac, char **av)
{
	int		i;
	int		f;

	i = 1;
	f = 0b0000;
	if (ac > 1)
	{
		while (ft_strncmp(av[i], "-", 1) == 0)
		{
			if (set_flag(av[i], &f))
				i++;
			else
				break;
		}
		while (i < ac)
		{
			write(1, av[i], ft_strlen(av[i]));
			if (i != ac - 1)
				write(1, " ", 1);
			i++;
		}
		if (!(f & 0b1000))
			write(1, "\n", 1);
		return (0);
	}
}
