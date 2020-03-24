#include "minishell.h"
#include "tokens.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

int	get_cmd_length(t_lex_lst *head)
{
	int	i;

	i = 0;
	while (head && head->token == WORD)
	{
		i++;
		head = head->next;
	}
	return (i);
}

/*int	do_pipe(t_lex_lst *c1, t_lex_lst *c2, char **env)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		return (-1);
	get_simple_cmd(c1, env);
	return (0);
}
*/
int	check_builtin(char **smp_cmd, char **env)
{
	int	i;

	i = execve(ft_strjoin(BUILTINS_PATH, smp_cmd[0]), smp_cmd, env);
	return (i);
}

int	get_simple_cmd(t_lex_lst *head, char **env)
{
	t_lex_lst	*cur;
	int		i;
	char		**smp_cmd;
	char		*path;
	char		**paths;
       
	cur = head;
	i = get_cmd_length(head);
	smp_cmd = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (cur && cur->token == WORD)
	{
	       smp_cmd[i++] = cur->raw;
	       cur = cur->next;
	}
	smp_cmd[i] = 0;
	check_builtin(smp_cmd, env);
	path = get_env_var("PATH=", env);
	paths = ft_split(path, ':');
	path = ft_strjoin("/", head->raw);
	i = 0;
	while (paths[i] && 0 > execve(ft_strjoin(paths[i], path), smp_cmd, env))
		i++;
	return (0);
}
