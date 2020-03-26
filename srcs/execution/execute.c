/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 09:12:20 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/26 17:54:20 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int						g_chpid;
extern struct termios	g_save;
int						g_exitcode;

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
	int exelen;

	exelen = ft_strlen(exename) + 1;
	if (ft_strncmp("cd", exename, exelen) == 0)
		return (&ms_cd);
	if (ft_strncmp("echo", exename, exelen) == 0)
		return (&ms_echo);
	if (ft_strncmp("env", exename, exelen) == 0)
		return (&ms_env);
	if (ft_strncmp("exit", exename, exelen) == 0)
		return (&ms_exit);
	if (ft_strncmp("pwd", exename, exelen) == 0)
		return (&ms_pwd);
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
		g_exitcode = f(arglen(av), av, env);
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
			exit(127);
		}
		else
		{
			g_chpid = pid;
			waitpid(pid, &g_exitcode, 0);

			if (WIFEXITED(g_exitcode))
        		g_exitcode = WEXITSTATUS(g_exitcode);
		}
	}
}
