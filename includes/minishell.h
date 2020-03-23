/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 15:11:13 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/23 18:34:42 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>
# include <sys/wait.h>
# include "libft.h"

# define HISTORY_PATH "/tmp/minishell_history"

typedef struct			s_cmd
{
	char				*raw;
	size_t				cpos;
	size_t				len;
	size_t				capacity;
}						t_cmd;

typedef	struct			s_lex_lst
{
	char				*raw;
	int					token;
	struct s_lex_lst	*next;
}						t_lex_lst;

int					minishell(char **env);
void				prompt(char **env);
char				*get_env_var(char *var_name, char **env);
void				save_cmd(char *line, char *path);
t_cmd				*new_cmd();
t_bool				push(char c, t_cmd *cmd);
t_bool				pop(t_cmd *cmd);
t_bool				stretch(t_cmd *cmd);
t_bool 				can_move_cursor_left(t_cmd *cmd);
t_bool 				can_move_cursor_right(t_cmd *cmd);
t_bool 				join_commands(t_cmd *c1, char *c2);
void				erase(t_cmd *cmd);
char				*get_cmd();
void				enable_raw_mode();
void				move_cursor_left(int x);
void				move_cursor_right(int x);
void				fill_with(char c, size_t len);
t_lex_lst			*lexer(char *str);
t_lex_lst			*lex_lstnew(void);
int					lex_quote(char *str, t_lex_lst *cur);
int					lex_newline(char *str, t_lex_lst *cur);
int					lex_redirect(char *str, t_lex_lst *cur);
int					lex_word(char *str, t_lex_lst *cur);
int					lex_variable(char *str, t_lex_lst *cur);
void				ctrlc_handler(int signal);

#endif
