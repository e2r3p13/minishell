#include "minishell.h"
#include "tokens.h"

void	redirect_great(t_rdct *cur, char **env)
{
	char	**name;
	int	fd[2];

	fd[1] = dup(STDOUT_FILENO);
	close(STDOUT_FILENO);
	name = (char**)cur->right;
	fd[0] = open(name[0], O_CREAT | O_WRONLY | O_TRUNC, 77777);
	dup2(fd[0], STDOUT_FILENO);
	if (sizeof(cur->left) == sizeof(cur))
		tree_exec(cur->left, env);
	else
		execute(cur->left, env);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
}

void	redirect_dgreat(t_rdct *cur, char **env)
{
	char	**name;
	int	fd[2];
	int	i;
	char	c;

	i = 1;
	fd[1] = dup(STDOUT_FILENO);
	close(STDOUT_FILENO);
	name = (char**)cur->right;
	fd[0] = open(name[0], O_RDWR | O_CREAT, 77777);
	while (i > 0)
		i = read(fd[0], &c, 1);
	dup2(fd[0], STDOUT_FILENO);
	if (sizeof(cur->left) == sizeof(cur))
		tree_exec(cur->left, env);
	else
		execute(cur->left, env);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
}

void	redirect_less(t_rdct *cur, char **env)
{
	char	**name;
	int	fd[2];

	fd[1] = dup(STDIN_FILENO);
	close(STDIN_FILENO);
	name = (char**)cur->right;
	fd[0] = open(name[0], O_RDONLY);
	dup2(fd[0], STDIN_FILENO);
	if (sizeof(cur->left) == sizeof(cur))
		tree_exec(cur->left, env);
	else
		execute(cur->left, env);
	close(fd[0]);
	dup2(fd[1], STDIN_FILENO);
	close(fd[1]);
}

void	redirect_pipe(t_rdct *cur, char **env)
{
	int	fd[2];
	int	fd_save[2];

	fd_save[0] = dup(STDIN_FILENO);
	fd_save[1] = dup(STDOUT_FILENO);
	pipe(fd);
	dup2(fd[1], STDOUT_FILENO);
	if (sizeof(cur->left) == sizeof(cur))
		tree_exec(cur->left, env);
	else
		execute(cur->left, env);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_save[1], STDOUT_FILENO);
	execute(cur->right, env);
	printf("done executing\n");
	dup2(fd_save[0], STDIN_FILENO);
	close(fd[0]);
	close(fd_save[0]);
	close(fd[1]);
	close(fd_save[1]);
}

void	tree_exec(t_rdct *cur, char **env)
{
	if (cur->type == GREAT)
		redirect_great(cur, env);
	else if (cur->type == DGREAT)
		redirect_dgreat(cur, env);
	else if (cur->type == LESS)
		redirect_less(cur, env);
	else if (cur->type == PIPE)
		redirect_pipe(cur, env);
	else
		execute(cur->left, env);
}

void	tab_free(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	tree_free(t_rdct *cur)
{
	if (cur->type != 0)
		tree_free(cur->left);
	else
		tab_free(cur->left);
	tab_free(cur->right);
	free(cur);
}
