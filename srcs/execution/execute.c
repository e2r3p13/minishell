/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 09:12:20 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/02 10:11:38 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int						g_chpid;
extern struct termios	g_save;
int						g_exitcode;

// Return the length of a (char **) array
static int arglen(char **av)
{
	int i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

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
	if (ft_strncmp("exit", exename, exelen) == 0)
		return (&ms_exit);
	if (ft_strncmp("pwd", exename, exelen) == 0)
		return (&ms_pwd);
	return (NULL);
}

// Turn a lexed list into an array of parameters of type (char **)
char 		**lex_to_args(t_lxr *lst)
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

// Execute the command given by av. Note that we don't know yet if the command
// is an executable or a builtin, this function figures out itself.
// This function also set the exitcode status with the return value of the last
// executed command
void		execute(char **av, char **env)
{
	int	pid;
	int	(*f)(int ac, char **av, char **env);

	if (av[0] == NULL)
		return ;
	if ((f = get_builtin_func(av[0])))
		g_exitcode = f(arglen(av), av, env);
	else
	{
		pid = fork();
		if (pid == 0)
			execute_binary(av, env);
		else
		{
			g_chpid = pid;
			waitpid(pid, &g_exitcode, 0);
			if (WIFEXITED(g_exitcode))
        		g_exitcode = WEXITSTATUS(g_exitcode);
		}
	}
}

// Perform the execution if the given command isn't a builtin
void execute_binary(char **av, char **env)
{
	char	**pathes;
	char	*relpath;
	char	*exepath;
	int		i;

	pathes = ft_split(get_env_var("PATH=", env), ':');
	relpath = ft_strjoin("/", av[0]);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_save);
	i = 0;
	while (pathes[i])
	{
		exepath = ft_strjoin(pathes[i], relpath);
		execve(exepath, av, env);
		free(exepath);
		i++;
	}
	free(relpath);
	ft_free_array(pathes);
	write(1, "minishell: command not found: ", 30);
	write(1, av[0], ft_strlen(av[0]));
	write(1, "\n", 1);
	exit(127);
}
