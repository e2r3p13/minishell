/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 20:31:20 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/08 20:31:05 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	term_enable_raw_mode(void)
{
	struct termios raw;

	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag &= ~(ICANON);
	raw.c_lflag &= ~(ECHO);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void	term_move_cursor(t_dir dir, int x)
{
	if (x > 0)
	{
		write(1, "\033[", 2);
		ft_putnbr(x);
		if (dir == left)
			write(1, "D", 1);
		else
			write(1, "C", 1);
	}
}

void	term_writen(char c, size_t len)
{
	char *s;

	if ((s = malloc(sizeof(char) * len)))
	{
		ft_memset(s, c, len);
		write(1, s, len);
		free(s);
	}
}

char	*append_backslash(char *mch)
{
	char *tmp;

	if ((tmp = ft_strjoin(mch, "/")))
	{
		free(mch);
		return (tmp);
	}
	return (mch);
}
