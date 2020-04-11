/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 15:11:13 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/11 17:12:24 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>
# include <stdio.h>

# define SCRIPT_PATH "/tmp/git_prompt.sh"
# define HISTORY_PATH "/tmp/minishell_history"

typedef struct s_env	t_env;
typedef struct s_hst	t_hst;
typedef struct s_lxr	t_lxr;
typedef struct s_psr	t_psr;
typedef struct dirent	t_ent;
typedef enum e_dir		t_dir;

/*
** s_env stores environment variables in a linked list, to make it easier to
** export / unset variables env argument of program main argument is never used
** once s_env has been set
*/

struct		s_env
{
	char	*key;
	char	*value;
	t_env	*next;
};

/*
** s_hst is a double linked list where all lines from minishell_history file
** are stored as an element, history is set at the beginning of the program and
** new elements are added each time user enter a command
*/

struct		s_hst
{
	char	*cmd;
	t_hst	*next;
	t_hst	*prev;
};

/*
** s_lxr stores tokens in a linked list. Each token have a token value,
** a raw that have been allocated then copied from a portion of command,
** and a space field, indicating weither the token is followed by a space or
** not in the command, useful to join tokens later if necessary
*/

struct		s_lxr
{
	char	*raw;
	int		token;
	t_bool	space;
	t_lxr	*next;
};

/*
** s_psr is a linked list with two 'next' elements, which is used to build
** an execution tree. The then execution's functions just have to follow the
** tree from root to leafs
*/

struct		s_psr
{
	int		type;
	void	*left;
	void	*right;
};

/*
** r_dir enum is used for some functions that needs more informations to work
*/

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

int			minishell(t_env *env, t_hst **hst, t_bool it);

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
char		*get_it_cmd(t_hst **hst);
char		*get_cmd(void);

/*
** Characters handling for interactive user input in command line
*/

int			handle_printable_char(t_dynstr *d, size_t *c, char *b, t_hst **h);
int			handle_backspace(t_dynstr *d, size_t *c);
int			handle_del(t_dynstr *d, size_t *c);
int			handle_return(t_dynstr *d, size_t *c, char *b, t_hst **h);
int			handle_escape(t_dynstr *d, size_t *c, char *b, t_hst **h);
int			handle_arrow(t_dynstr *d, size_t *c, t_dir dir);
int			handle_fnarrow(t_dynstr *d, size_t *c, t_dir dir);
int			handle_optleft(t_dynstr *d, size_t *c);
int			handle_optright(t_dynstr *d, size_t *c);
int			handle_history(t_dynstr *d, size_t *c, t_hst **h, t_dir dir);
int			handle_ctrld(t_dynstr *d, size_t *c);
int			handle_ctrlp(t_dynstr *d, size_t *c, char *b, t_hst **h);
int			handle_ctrln(t_dynstr *d, size_t *c, char *b, t_hst **h);
int			handle_ctrlu(t_dynstr *d, size_t *c);
int			handle_ctrlk(t_dynstr *d, size_t *c);
int			handle_ctrlh(t_dynstr *d, size_t *c);
int			handle_ctrlc(t_dynstr *d);
int			handle_tab(t_dynstr *d, size_t *c);

char		*find_match(DIR *dir, char *word, t_ent *ent);
char		*find_all_matches(DIR *dir, char *word, char *path, t_ent *ent);

/*
** History functions
*/

t_hst		*hst_get(void);
int			hst_push(t_hst **hst, char *cmd);
void		hst_free(t_hst *hst);
void		hst_print(t_hst *hst);
void		hst_pop(t_hst **hst);
void		hst_replace_last(t_hst **hst);
void		hst_save(char *cmd);

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
void			lxr_append(t_lxr **end);

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
char		*find_path(char **word);
int		wd_mch(char *s1, char *s2);
int		match_nb(DIR *dir, char *s, char *pth);
int			join_unspaced_words(t_lxr *lst);
char		**lex_to_args(t_lxr *lst);

/*
**-------------**
**			   **
**    Parser   **
**			   **
**-------------**
*/

t_psr		*parser(t_lxr *lst);

/*
**------------------------------------**
**								 	  **
**    Exectution relative functions   **
**								  	  **
**------------------------------------**
*/

void		tree_exec(t_psr *cur, t_env *env);
void		redirect_less(t_psr *cur, t_env *env);
void		redirect_pipe(t_psr *cur, t_env *env);
void		redi_err(t_psr *head, int fd, int std, char *file);
void		tree_free(t_psr *cur);
void		tweak_tree_exec(t_psr *cur, t_env *env);
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
