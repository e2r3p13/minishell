/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 09:12:20 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/25 21:30:46 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int						g_chpid;
extern struct termios	g_save;

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
	while (lst && lst->token)
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
	int		pid;
	int		(*f)(int ac, char **av, char **env);

	if (av[0] == NULL)
		return ;
	if ((f = get_builtin_func(av[0])))
		f(arglen(av), av, env);
	else
	{
		pathes = ft_split(get_env_var("PATH=", env), ':');
		relpath = ft_strjoin("/", av[0]);
		pid = fork();
		if (pid == 0)
		{
			tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_save);
			i = 0;
			while (pathes[i])
			{
				exepath = ft_strjoin(pathes[i], relpath);
				execve(exepath, av, env);
				i++;
			}
			write(1, "minishell: command not found: ", 30);
			write(1, av[0], ft_strlen(av[0]));
			write(1, "\n", 1);
			exit(0);
		}
		else
		{
			g_chpid = pid;
			wait(0);
		}
	}
}
