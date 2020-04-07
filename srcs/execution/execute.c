/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 09:12:20 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/07 18:27:08 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

extern int	g_exitcode;

// Return a function pointer if exename match a builtin name, return NULL else
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
	if (ft_strncmp("unset", exename, exelen) == 0)
		return (&ms_unset);
	if (ft_strncmp("export", exename, exelen) == 0)
		return (&ms_export);
	if (ft_strncmp("exit", exename, exelen) == 0)
		return (&ms_exit);
	if (ft_strncmp("pwd", exename, exelen) == 0)
		return (&ms_pwd);
	return (NULL);
}

// Execute the command given by av. Note that we don't know yet if the command
// is an executable or a builtin, this function figures out itself.
// This function also set the exitcode status with the return value of the last
// executed command
void		execute(char **av, t_env *env)
{
	int	pid;
	int	(*f)(int ac, char **av, t_env *env);

	if (av[0] == NULL)
		return ;
	if ((f = get_builtin_func(av[0])))
		g_exitcode = f(arglen(av), av, env);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			execute_binary(av, env);
		}
		else
		{
			waitpid(pid, &g_exitcode, 0);
			if (WIFEXITED(g_exitcode))
        		g_exitcode = WEXITSTATUS(g_exitcode);
		}
	}
}

static int	cmd_not_found(char *msg)
{
	write(1, "minishell: command not found: ", 30);
	write(1, msg, ft_strlen(msg));
	write(1, "\n", 1);
	return (CMD_NOT_FOUND);
}

// Perform the execution if the given command isn't a builtin
void		execute_binary(char **av, t_env *env)
{
	char	**pathes;
	char	*relpath;
	char	*exepath;
	int		i;
	char	**e;

	e = env_to_arr(env);
	execve(*av, av, e);
	if ((exepath = get_env_var("PATH", env)))
	{
		pathes = ft_split(exepath, ':');
		relpath = ft_strjoin("/", av[0]);
		i = 0;
		while (pathes[i])
		{
			exepath = ft_strjoin(pathes[i], relpath);
			execve(exepath, av, e);
			free(exepath);
			i++;
		}
		free(relpath);
		ft_free_array(pathes);
	}
	ft_free_array(e);
	exit(cmd_not_found(av[0]));
}
