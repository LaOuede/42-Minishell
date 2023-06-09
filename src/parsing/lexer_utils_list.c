#include "../../include/minishell.h"

void	ft_merge(t_token *node, t_token *next)
{
	printf(KYEL "-------------------- FT_MERGE" KGRN " START " RESET KYEL "--------------------\n" RESET);
	char	*new_str;
	char	*tmp;

	new_str = NULL;
	tmp = NULL;
	if (next->ws == 1)
		node->str = ft_strjoin_char(node->str, ' ');
	new_str = ft_strjoin(node->str, next->str);
	tmp = node->str;
	node->str = ft_strdup(new_str);
	ft_freenull(tmp);
	ft_freenull(new_str);
	printf("ptr->str = %s\n", node->str);
	printf("ptr->next->str = %s\n", next->str);
	printf(KYEL "-------------------- FT_MERGE" KRED " END " RESET KYEL "--------------------\n" RESET);
}

t_token	*ft_create_node(char *str, t_pars *pars)
{
	t_token	*new_node;

	new_node = ft_calloc(1, sizeof(t_token));
	new_node->type = pars->type;
	new_node->str = ft_strdup(str);
	new_node->nb_cmd = pars->nb_pipe;
	new_node->s_quotes = pars->s_quotes;
	new_node->d_quotes = pars->d_quotes;
	new_node->c_brackets = pars->c_brackets;
	new_node->ws = pars->flag_whitespace;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	ft_add_token_bottom(t_token **lst, t_token *new_node)
{
	t_token	*last;

	if (!new_node)
		return ;
	if (*lst == NULL)
	{
		*lst = new_node;
		new_node->prev = NULL;
		new_node->next = NULL;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
}
