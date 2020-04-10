/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 15:11:13 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/10 15:12:47 by lfalkau          ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/stat.h>
# include "keys.h"

# define HISTORY_PATH "/tmp/minishell_history"

# define CMD_NOT_FOUND 127

typedef struct s_env	t_env;
typedef struct s_hst	t_hst;
typedef struct s_lxr	t_lxr;
typedef struct s_rdct	t_rdct;
typedef enum e_dir		t_dir;

struct		s_env
{
	char	*key;
	char	*value;
	t_env	*next;
};

struct		s_hst
{
	char	*cmd;
	t_hst	*next;
	t_hst	*prev;
};

struct		s_lxr
{
	char	*raw;
	int		token;
	t_bool	space;
	t_lxr	*next;
};

struct		s_rdct
{
	int		type;
	void	*left;
	void	*right;
};

enum		e_dir
{
	left,
	right,
	up,
	down,
};

/*
**----------------**
**				  **
**    Minishell   **
**				  **
**----------------**
*/

int			minishell(t_env *env, t_hst *hst, t_bool it);

/*
**-------------------------------**
**								 **
**    Input relative functions   **
**								 **
**-------------------------------**
*/

/*
** Main input functions, including user input and prompt functions
*/

void		prompt(t_env *env);
char		*get_it_cmd(void);
char		*get_cmd(void);

/*
** Characters handling for interactive user input in command line
*/

int			handle_printable_char(char *b, size_t *c, t_dynstr *d);
int			handle_backspace(char *b, size_t *c, t_dynstr *d);
int			handle_del(char *b, size_t *c, t_dynstr *d);
int			handle_return(char *b, size_t *c, t_dynstr *d);
int			handle_escape(char *b, size_t *c, t_dynstr *d);
int			handle_arrow(char *b, size_t *c, t_dynstr *d, t_dir dir);
int			handle_fnarrow(char *b, size_t *c, t_dynstr *d, t_dir dir);
int			handle_optleft(char *b, size_t *c, t_dynstr *d);
int			handle_optright(char *b, size_t *c, t_dynstr *d);
int			handle_history(char *b, size_t *c, t_dynstr *d, t_dir dir);
int			handle_ctrld(char *b, size_t *c, t_dynstr *d);
int			handle_ctrlu(char *b, size_t *c, t_dynstr *d);
int			handle_ctrlk(char *b, size_t *c, t_dynstr *d);
int			handle_ctrlh(char *b, size_t *c, t_dynstr *d);
int			handle_ctrlc(char *buf, size_t *cpos, t_dynstr *dstr);
int			handle_tab(char *b, size_t *c, t_dynstr *d);

/*
** History functions
*/

t_hst		*hst_get(void);
int			hst_push(t_hst **hst, char *cmd);
void		hst_pop(t_hst **hst);
void		hst_free(t_hst *hst);

/*
** Input utils, often terminal sequences writing
*/

void		enable_raw_mode(void);
void		disable_raw_mode(void);
void		move_cursor(t_dir dir, int x);
int			writen(char c, size_t l);

/*
**-------------------------------**
**								 **
**    Lexer relative functions   **
**								 **
**-------------------------------**
*/

/*
** Main lexer part, including global behaviour, grammar and splitting
*/

t_lxr		*lexer(char *str);
t_lxr		*lxr_check_grammar(t_lxr *head);
t_lxr		**lxr_split(t_lxr *head);
t_lxr		*lxr_get_cmd_head(t_lxr **head);
t_lxr		*lxr_lstnew(void);
void		*lxr_free(t_lxr *head);
int			lstsize(t_lxr *lst);
void		lxr_print(t_lxr **lst);

/*
** Helper functions to lex each part of cmd into tokens
*/

int			lxr_newline(char *str, t_lxr *cur);
int			lxr_redirect(char *str, t_lxr *cur);
int			lxr_quote(char *str, t_lxr *cur);
int			lxr_word(char *str, t_lxr *cur);
int			lxr_variable(char *str, t_lxr *cur);

/*
** Expand variables / exit codes / quoted tokens etc...
*/

int			expand(t_lxr *lst, t_env *env);
char		*remove_quotes(char *raw);
int			expand_squotes(t_lxr *lst);
int			expand_dquotes(t_lxr *lst, t_env *env);
int			expand_wcard(t_lxr **head, t_lxr *cur);
char		*expand_variable(char *raw, t_env *env);
char		*expand_exitcode(char *raw);
char		*expand_quoted_dollar(char *r, char *v, size_t l, t_env *e);
char		*wildcard_to_str(char *str);
int			join_unspaced_words(t_lxr *lst);
char		**lex_to_args(t_lxr *lst);

/*
**-------------**
**			   **
**    Parser   **
**			   **
**-------------**
*/

t_rdct		*parser(t_lxr *lst);

/*
**------------------------------------**
**								 	  **
**    Exectution relative functions   **
**								  	  **
**------------------------------------**
*/

void		tree_exec(t_rdct *cur, t_env *env);
void		redirect_less(t_rdct *cur, t_env *env);
void		redirect_pipe(t_rdct *cur, t_env *env);
void		redi_err(t_rdct *head, int fd, int std, char *file);
void		tree_free(t_rdct *cur);
void		tweak_tree_exec(t_rdct *cur, t_env *env);
void		execute(char **argv, t_env *env);
void		execute_binary(char **av, t_env *env);

/*
**---------------**
**				 **
**    Builtins   **
**				 **
**---------------**
*/

int			ms_cd(int ac, char **av, t_env *env);
int			ms_echo(int ac, char **av);
int			ms_env(int ac, char **av, t_env *env);
int			ms_export(int ac, char **av, t_env *env);
int			ms_pwd(int ac, char **av);
int			ms_unset(int ac, char **av, t_env *env);

/*
**----------------------**
**						**
**    Other functions   **
**						**
**----------------------**
*/

char		*get_env_var(char *var_name, t_env *env);
void		sighandler(int signal);
int			arglen(char **av);
int			open_reg_file(char *path, int flags, mode_t mode);
int			open_file(char *path, int flags, mode_t mode);
t_env		*env_get(char **e);
void		env_print(t_env *env);
void		*env_free(t_env *env);
char		**env_to_arr(t_env *env);
int			env_size(t_env *env);
int			env_push_back(t_env *env, char *key, char *value);
void		env_remove_first(t_env *env);
void		env_remove_elm(t_env *env, t_env *elm);
char		*append_backslash(char *mch);

#endif
