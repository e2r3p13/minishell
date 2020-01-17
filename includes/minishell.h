/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 15:11:13 by lfalkau           #+#    #+#             */
/*   Updated: 2020/01/17 12:24:54 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"

# define PROMPT "\033[94m » \033[0m"
# define PROMPT_GIT "\033[33m -\033[0m"
# define PROMPT_GIT_MODIFIED "\033[33m *\033[0m"

int		minishell(char **env);
void	prompt(char **env);
char	*get_env_var(char *var_name, char **env);

#endif
