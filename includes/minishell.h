/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 15:11:13 by lfalkau           #+#    #+#             */
/*   Updated: 2020/01/20 23:13:34 by lfalkau          ###   ########.fr       */
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

# ifndef GDD_PATH
#  define GDD_PATH "/sgoifre/goinfre/Perso/lfalkau/gdd.sh"
# endif

# ifndef PATH_COLOR
#  define PATH_COLOR "\033[36m"
# endif

int		minishell(char **env, char *exec_path);
void	prompt(char **env, char *exec_path);
char	*get_env_var(char *var_name, char **env);
void	save_command(char *line, char *path);

#endif
