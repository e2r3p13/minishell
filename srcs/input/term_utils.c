/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 20:31:20 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/10 17:29:00 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

struct termios	g_oldterm;

void	enable_raw_mode(void)
{
	struct termios newterm;

	tcgetattr(STDIN_FILENO, &g_oldterm);
	tcgetattr(STDIN_FILENO, &newterm);
	newterm.c_lflag &= ~(ICANON);
	newterm.c_lflag &= ~(ECHO);
	newterm.c_cc[VINTR] = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &newterm);
}

void	disable_raw_mode(void)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_oldterm);
}

void	move_cursor(t_dir dir, int x)
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

int		writen(char c, size_t l)
{
	char *s;

	if ((s = malloc(sizeof(char) * l)))
	{
		ft_memset(s, c, l);
		write(1, s, l);
		free(s);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
