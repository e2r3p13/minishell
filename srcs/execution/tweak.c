#include "minishell.h"
#include "tokens.h"

static void    tweak_great(t_rdct *cur, t_env *env)
{
        char    **name;
        int     fd[2];

        name = (char**)cur->right;
        fd[0] = open(name[0], O_CREAT | O_WRONLY | O_TRUNC, 77777);
        if (sizeof(cur->left) == sizeof(cur))
                tweak_tree_exec(cur->left, env);
        else
                execute(cur->left, env);
        close(fd[0]);
}

static void    tweak_dgreat(t_rdct *cur, t_env *env)
{
        char    **name;
        int     fd[2];
        int     i;
        char    c;

        i = 1;
        name = (char**)cur->right;
        fd[0] = open(name[0], O_RDWR | O_CREAT, 77777);
        while (i > 0)
                i = read(fd[0], &c, 1);
        if (sizeof(cur->left) == sizeof(cur))
                tweak_tree_exec(cur->left, env);
        else
                execute(cur->left, env);
        close(fd[0]);
}

void	tweak_tree_exec(t_rdct *cur, t_env *env)
{
  if (cur->type == GREAT)
                tweak_great(cur, env);
        else if (cur->type == DGREAT)
                tweak_dgreat(cur, env);
        else if (cur->type == LESS)
                redirect_less(cur, env);
        else if (cur->type == PIPE)
                redirect_pipe(cur, env);
        else
                execute(cur->left, env);
        tree_free(cur);
}
