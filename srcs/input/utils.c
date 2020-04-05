/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 20:31:20 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/07 16:09:00 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Switch terminal to canocical mode
void	term_enable_raw_mode()
{
	struct termios raw;

	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag &= ~(ICANON);
	raw.c_lflag &= ~(ECHO);
	// raw.c_cc[VTIME] = 0;
	// raw.c_cc[VMIN] = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

// Move the printed cursor by 'x' in 'dir' direction
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

// Write 'len' times the 'c' char, trying to do as less write calls as possible
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

// Appends a '/' at the end of a string and return itself, return inchanged
// string if failed
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
