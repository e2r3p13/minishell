#include "minishell.h"
#include "tokens.h"
#include "libft.h"

static int lstsize(t_lxr *lst)
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

static char            **lex_to_arg(t_lxr *lst)
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

static char	**create_simple_cmd(t_lxr **head)
{
	char	**cmd;

	cmd = lex_to_arg(*head);
	while (*head && (*head)->token == WORD)
		*head = (*head)->next;
	return (cmd);
}
		

static t_rdct	*create_redirect_cmd(void *left, t_lxr **cur)
{
	t_rdct	*lst_head;

	if (!(lst_head = (t_rdct *)malloc(sizeof(t_rdct))))
		return (NULL);
	lst_head->left = left;
	if (!cur)
	{
		lst_head->type = 0;
		lst_head->right = NULL;
		return (lst_head);
	}
	if (!(*cur) || (*cur)->token != REDIRECT)
		lst_head->type = 0;
	else if (!ft_strncmp((*cur)->raw, "|", 2))
		lst_head->type = PIPE;
	else if (!ft_strncmp((*cur)->raw,"<", 2))
		lst_head->type = LESS;
//	else if (!ft_strncmp((*cur)->raw, "<<", 3))//useless
//		lst_head->type = DLESS;
	else if (!ft_strncmp((*cur)->raw, ">", 2))
		lst_head->type = GREAT;
	else if (!ft_strncmp((*cur)->raw, ">>", 3))
		lst_head->type = DGREAT;
	if (*cur)
		*cur = (*cur)->next;
	lst_head->right = create_simple_cmd(cur);
	return (lst_head);
}

t_rdct		*parser(t_lxr *cur)
{
	void		*prs_head;
	char		**cmd;

	prs_head = NULL;
	cmd = create_simple_cmd(&cur);
	prs_head = create_redirect_cmd(cmd, NULL);
	if (!cur)
		return (prs_head);
	while (cur && cur->token == REDIRECT)
		prs_head = create_redirect_cmd(prs_head, &cur);
	return (prs_head);
}
