/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 15:11:13 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/20 11:55:04 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
#include <termios.h>
# include "libft.h"

# define HISTORY_PATH "/tmp/minishell_history"

typedef struct	s_cmd
{
	char		*raw;
	size_t		cpos;
	size_t		len;
	size_t		capacity;
}				t_cmd;

int				minishell(char **env);
void			prompt(char **env);
char			*get_env_var(char *var_name, char **env);
void			save_cmd(char *line, char *path);
t_cmd			*new_cmd();
t_bool			push(char c, t_cmd *cmd);
t_bool			pop(t_cmd *cmd);
t_bool			stretch(t_cmd *cmd);
t_bool 			move_cursor_left(t_cmd *cmd);
t_bool 			move_cursor_right(t_cmd *cmd);
t_bool 			join_commands(t_cmd *c1, char *c2);
char			*get_cmd();
void			enable_raw_mode();
void			int_handler(int signal);
void			term_handler(int signal);

#endif
