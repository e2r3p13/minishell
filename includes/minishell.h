/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 15:11:13 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/28 20:36:08 by lfalkau          ###   ########.fr       */
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
# include <errno.h>
# include "libft.h"

# define HISTORY_PATH "/tmp/minishell_history"
# define BUILTINS_PATH "./builtins/"

typedef struct			s_cmd
{
	char				*raw;
	size_t				cpos;
	size_t				len;
	size_t				capacity;
}						t_cmd;

typedef struct		s_hst
{
	t_cmd			*cmd;
	struct	s_hst	*next;
	struct	s_hst	*prev;
}					t_hst;

typedef	struct			s_lex_lst
{
	char				*raw;
	int					token;
	t_bool				space;
	struct s_lex_lst	*next;
}						t_lex_lst;

typedef struct			s_rdct
{
	int					type;
	void				*left;
	void				*right;
}						t_rdct;

typedef enum			e_dir
{
	left,
	right,
}						t_dir;

//					main functions
int					minishell(char **env);

//					Generic functions
char				*get_env_var(char *var_name, char **env);
void				ctrlc_handler(int signal);

//					input functions
void				prompt(char **env);
void				prompt_path(char **env);
void				save_cmd(t_cmd *line);
t_cmd				*new_cmd();
t_bool				push(char c, t_cmd *cmd);
t_bool				pop(t_cmd *cmd);
t_bool				stretch(t_cmd *cmd);
t_bool 				can_move_cursor(t_cmd *cmd, t_dir dir);
void				move_cursor(t_dir dir, int x);
void				erase(t_cmd *cmd);
void				free_cmd(t_cmd *cmd);
char				*get_cmd(t_hst **hst);
void				enable_raw_mode();
void				fill_with(char c, size_t len);
char				*cmd_return(t_hst *hst);
void				cmd_arrows(t_hst **hda, char *buf);
void				cmd_backspace(t_cmd *cmd);
void				cmd_character(t_cmd *cmd, char *buf);
t_bool				cmd_ctrld_shoould_exit(t_cmd *cmd);
void				cmd_ctrlu(t_cmd *cmd);
void				free_hst(t_hst	*hst);
int					push_back_hst(t_hst **hst, t_cmd *cmd);
t_hst				*get_hst(void);
void				pop_back_hst(t_hst	*hst);
int					use_old_cmd(t_hst **hst, t_cmd *cmd);

//					lexer functions
t_lex_lst			*lexer(char *str);
t_lex_lst			*lex_lstnew(void);
int					lex_quote(char *str, t_lex_lst *cur);
int					lex_newline(char *str, t_lex_lst *cur);
int					lex_redirect(char *str, t_lex_lst *cur);
int					lex_word(char *str, t_lex_lst *cur);
int					lex_variable(char *str, t_lex_lst *cur);

//					lexer - parser transitional functions
t_bool				expand(t_lex_lst *lst, char **env);
char				*remove_quotes(char *raw);
t_bool				expand_squotes(t_lex_lst *lst);
t_bool				expand_dquotes(t_lex_lst *lst, char **env);
char				*expand_variable(char *raw, char **env);
char				*expand_exitcode(char *raw);
char				*expand_quoted_dollar(char *r, char *v, size_t l, char **e);
void				join_unspaced_words(t_lex_lst *lst);
char 				**lex_to_args(t_lex_lst *lst);

//					parser functions
t_rdct				*parser(t_lex_lst *lst);
void				execute(char **, char **env);

//					exectution's functions

//					Builtins functions
int					ms_cd(int ac, char **av, char **env);
int					ms_echo(int ac, char **av);
int					ms_env(int ac, char **av, char **env);
int					ms_exit(int ac, char **av, char **env);
int					ms_export(int ac, char **av);
int					ms_pwd(int ac, char **av, char **env);
int					ms_unset(int ac, char **av);

#endif
