/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 15:11:13 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/30 13:26:04 by lfalkau          ###   ########.fr       */
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
	size_t				pos;
	size_t				len;
	size_t				capacity;
}						t_cmd;

typedef struct			s_hst
{
	t_cmd				*cmd;
	struct	s_hst		*next;
	struct	s_hst		*prev;
}						t_hst;

typedef	struct			s_lxr
{
	char				*raw;
	int					token;
	t_bool				space;
	struct s_lxr		*next;
}						t_lxr;

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
int					minishell(char **env, t_hst *history);

//					Generic functions
char				*get_env_var(char *var_name, char **env);
void				ctrlc_handler(int signal);

//					input functions
void				prompt(char **env);
t_cmd				*cmd_get(char **env, t_hst **hst);
t_cmd				*cmd_new();
void				cmd_save(t_cmd *line);
t_bool				cmd_push_char(char c, t_cmd *cmd);
t_bool				cmd_pop_char(t_cmd *cmd);
t_bool				cmd_stretch(t_cmd *cmd);
t_bool 				cmd_can_move_cursor(t_cmd *cmd, t_dir dir);
void				cmd_erase(t_cmd *cmd);
void				*cmd_free(t_cmd *cmd);
t_hst				*hst_get(void);
void				*hst_free(t_hst *hst);
t_bool				hst_push_cmd(t_hst **hst, t_cmd *cmd);
void				hst_pop_cmd(t_hst **hst);
t_bool				hst_reuse_cmd(t_hst **hst, t_cmd *cmd);
void				term_move_cursor(t_dir dir, int x);
void				term_enable_raw_mode();
void				term_writen(char c, size_t len);
void				cmd_esc_seq(t_hst **hda, char *buf);
void				cmd_handle_backspace(t_cmd *cmd);
void				cmd_handle_character(t_cmd *cmd, char *buf);
t_bool				cmd_handle_ctrld(t_cmd *cmd);
void				cmd_handle_ctrlu(t_cmd *cmd);
t_cmd				*cmd_handle_return(t_hst *hst);
void				cmd_handle_tab(t_cmd *cmd);
char				*append_backslash(char *mch); // add to libft in a generic way

//					lexer functions
t_lxr				*lexer(char *str);
t_lxr				*lxr_lstnew(void);
t_lxr				*lxr_check_grammar(t_lxr *head);
t_lxr				**lxr_split(t_lxr *head);
t_lxr				*lxr_get_cmd_head(t_lxr **head);
void				*lxr_free(t_lxr *head);
int					lxr_quote(char *str, t_lxr *cur);
int					lxr_newline(char *str, t_lxr *cur);
int					lxr_redirect(char *str, t_lxr *cur);
int					lxr_word(char *str, t_lxr *cur);
int					lxr_variable(char *str, t_lxr *cur);
void				lxr_print(t_lxr **lst);

//					lexer - parser transitional functions
t_bool				expand(t_lxr *lst, char **env);
char				*remove_quotes(char *raw);
t_bool				expand_squotes(t_lxr *lst);
t_bool				expand_dquotes(t_lxr *lst, char **env);
char				*expand_variable(char *raw, char **env);
char				*expand_exitcode(char *raw);
char				*expand_quoted_dollar(char *r, char *v, size_t l, char **e);
t_bool				join_unspaced_words(t_lxr *lst);
char 				**lex_to_args(t_lxr *lst);

//					parser functions
t_rdct				*parser(t_lxr *lst);
void				execute(char **, char **env);

//					exectution's functions
void				tree_exec(t_rdct *cur, char **env);

//					Builtins functions
int					ms_cd(int ac, char **av, char **env);
int					ms_echo(int ac, char **av);
int					ms_env(int ac, char **av, char **env);
int					ms_exit(int ac, char **av, char **env);
int					ms_export(int ac, char **av);
int					ms_pwd(int ac, char **av, char **env);
int					ms_unset(int ac, char **av);

#endif
