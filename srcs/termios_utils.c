/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 20:31:20 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/23 15:26:43 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern struct termios g_ogterm;

void	enable_raw_mode()
{
	struct termios raw;

	tcgetattr(STDIN_FILENO, &g_ogterm);
	atexit(disable_raw_mode);
	raw = g_ogterm;
	raw.c_lflag &= ~(ICANON);
	raw.c_lflag &= ~(ECHO);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void	disable_raw_mode()
{
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_ogterm);
}

void	move_cursor_left(int x)
{
	if (x > 0)
	{
		write(1, "\033[", 2);
		ft_putnbr(x);
		write(1, "D", 1);
	}
}

void	move_cursor_right(int x)
{
	if (x > 0)
	{
		write(1, "\033[", 2);
		ft_putnbr(x);
		write(1, "C", 1);
	}
}

void	fill_with(char c, size_t len)
{
	char *s;

	if ((s = malloc(sizeof(char) * len)))
	{
		ft_memset(s, c, len);
		write(1, s, len);
		free(s);
	}
}
