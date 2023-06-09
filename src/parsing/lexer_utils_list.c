#include "../../include/minishell.h"

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
