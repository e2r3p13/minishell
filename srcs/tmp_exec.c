/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 09:12:20 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/25 13:36:15 by lfalkau          ###   ########.fr       */
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

static int arglen(char **av)
{
	int i;

	i = 0;
	while (av[i])
		i++;
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
	if (ft_strncmp("exit", exename, 3) == 0)
		return (&ms_exit);
	// if (ft_strncmp("export", exename, 3) == 0)
	// 	return (&ms_export);
	if (ft_strncmp("pwd", exename, 3) == 0)
		return (&ms_pwd);
	// if (ft_strncmp("unset", exename, 3) == 0)
	// 	return (&ms_unset);
	return (NULL);
}

char 		**lex_to_args(t_lex_lst *lst)
{
	char	**av;
	int		i;

	i = 0;
	av = malloc(sizeof(char *) * (lstsize(lst) + 1));
	while (lst)
	{
	       av[i++] = lst->raw;
	       lst = lst->next;
	}
	av[i] = NULL;
	return (av);
}

void		execute(char **av, char **env)
{
	char	**pathes;
	char	*relpath;
	char	*exepath;
	int		i;
	int		(*f)(int ac, char **av, char **env);

	if ((f = get_builtin_func(av[0])))
		f(arglen(av), av, env);
	else
	{
		i = 0;
		pathes = ft_split(get_env_var("PATH=", env), ':');
		relpath = ft_strjoin("/", av[0]);
		while (pathes[i])
		{
			exepath = ft_strjoin(pathes[i], relpath);
			if (fork() == 0)
			{
				execve(exepath, av, env);
				exit(0);
			}
			else
				wait(0);
			i++;
		}
	}
}
