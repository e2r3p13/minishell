#include "minishell.h"
#include "tokens.h"
#include "libft.h"

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

char            **lex_to_args(t_lex_lst *lst)
{
        char    **av;
        int             i;

        i = 0;
        av = malloc(sizeof(char *) * (lstsize(lst) + 1));
        while (lst && lst->token == WORD)
        {
               av[i++] = lst->raw;
               lst = lst->next;
        }
        av[i] = NULL;
        return (av);
}

static char	**create_simple_cmd(t_lex_lst **head)
{
	char	**cmd;

	cmd = lex_to_args(*head);
	while (*head && (*head)->token == WORD)
		*head = (*head)->next;
	return (cmd);
}
		

static t_rdct	*create_redirect_cmd(void *left, t_lex_lst **cur)
{
	t_rdct	*lst_head;

	if (!(lst_head = (t_rdct *)malloc(sizeof(t_rdct))))
		return (NULL);
	lst_head->left = left;
	if (!(*cur) || (*cur)->token != REDIRECT)
		lst_head->type = 0;
	else if (!ft_strncmp((*cur)->raw, "|", 2))
		lst_head->type = PIPE;
	else if (!ft_strncmp((*cur)->raw,"<", 2))
		lst_head->type = LESS;
	else if (!ft_strncmp((*cur)->raw, "<<", 3))
		lst_head->type = DLESS;
	else if (!ft_strncmp((*cur)->raw, ">", 2))
		lst_head->type = GREAT;
	else if (!ft_strncmp((*cur)->raw, ">>", 3))
		lst_head->type = DGREAT;
	if (*cur)
		*cur = (*cur)->next;
	lst_head->right = create_simple_cmd(cur);
	return (lst_head);
}

t_rdct		*parser(t_lex_lst *cur)
{
	void		*prs_head;
	char		**cmd;

	prs_head = NULL;
	cmd = create_simple_cmd(&cur);
	if (!cur)
		return (create_redirect_cmd(cmd, &cur));
	while (cur && cur->token == REDIRECT)
	{
		if (!prs_head)
			prs_head = create_redirect_cmd(cmd, &cur);
		else
			prs_head = create_redirect_cmd(prs_head, &cur);
	}
	return (prs_head);
}
