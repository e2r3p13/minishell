/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 15:11:13 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/18 20:24:48 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include "libft.h"

# define HISTORY_PATH "/tmp/minishell_history"

typedef struct	s_cmd
{
	char		*raw;
	size_t		len;
	size_t		capacity;
}				t_cmd;

int				minishell(char **env);
void			prompt(char **env);
char			*get_env_var(char *var_name, char **env);
void			save_cmd(char *line, char *path);
t_cmd			*new_cmd();
int				push(char c, t_cmd *cmd);
void			pop(t_cmd *cmd);
int				insert(char c, int index, t_cmd *cmd);
int				stretch(t_cmd *cmd);
void			delete(t_cmd *cmd);
char			*get_cmd();

#endif
