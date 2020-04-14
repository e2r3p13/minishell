/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 20:13:35 by lfalkau           #+#    #+#             */
/*   Updated: 2020/04/14 20:51:40 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			pipe_redirection(t_ast *ast, t_env *env)
{
	int fd[2];
    pid_t pid;
    pid_t pid2;

    pipe(fd);
    if ((pid = fork()) == 0)
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        execve(program_3[0], program_3, NULL);
    }
    else if (pid > 0)
    {
        if ( (pid2 = fork()) == 0) {
            dup2(fd[0], STDIN_FILENO);
            close(fd[1]);
            execve(program_2[0], program_2, NULL);
        }
    }

    waitpid(pid, 0, 0);
    waitpid(pid2, 0, 0);
    return (EXIT_SUCCESS);
}
