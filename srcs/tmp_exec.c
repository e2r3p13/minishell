/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 09:12:20 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/25 12:32:37 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int lstsize(t_lex_lst *lst)
{
	int i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

static void	*get_builtin_func(char *exename)
{
	if (ft_strncmp("cd", exename, 3) == 0)
		return (&ms_cd);
	if (ft_strncmp("echo", exename, 3) == 0)
		return (&ms_echo);
	if (ft_strncmp("env", exename, 3) == 0)
		return (&ms_env);
	// if (ft_strncmp("exit", exename, 3) == 0)
	// 	return (&ms_exit);
	// if (ft_strncmp("export", exename, 3) == 0)
	// 	return (&ms_export);
	if (ft_strncmp("pwd", exename, 3) == 0)
		return (&ms_pwd);
	// if (ft_strncmp("unset", exename, 3) == 0)
	// 	return (&ms_unset);
	return (NULL);
}

int			execute_builtin(t_lex_lst *lst, char **env)
{
	int			i;
	char		**av;
	int			(*f)(int ac, char **av, char **env);

	i = 0;
	av = malloc(sizeof(char *) * (lstsize(lst) + 1));
	while (lst)
	{
	       av[i++] = lst->raw;
	       lst = lst->next;
	}
	av[i] = NULL;
	if ((f = get_builtin_func(av[0])))
		f(i, av, env);
	else
	{
		write(1, "minishell: command not foud: ", 29);
		write(1, av[0], ft_strlen(av[0]));
		write(1, "\n", 1);
	}
	return (0);
}
