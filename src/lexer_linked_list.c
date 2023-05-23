#include "../include/minishell.h"

t_token	*ft_create_node(char *str, t_minishell *parse)
{
	t_token	*new_node;

	new_node = ft_calloc(1, sizeof(t_token));
	new_node->type = parse->type;
	new_node->str = ft_strdup(str);
	new_node->nb_cmd = parse->nb_pipe;
	new_node->s_quotes = parse->s_quotes;
	new_node->d_quotes = parse->d_quotes;
	new_node->p_brackets = parse->p_brackets;
	new_node->c_brackets = parse->c_brackets;
	new_node->ws = parse->flag_whitespace;
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
		return ;
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
}

void	ft_add_token(t_token **lst, t_token *new_node)
{
	t_token	*tmp1;
	t_token	*tmp2;

	if (!new_node)
		return ;
	if (*lst == NULL)
	{
		*lst = new_node;
		new_node->prev = NULL;
		return ;
	}
	tmp1 = *lst;
	tmp2 = tmp1->next;
	new_node->next = tmp1->next;
	new_node->prev = tmp1;
	tmp1->next = new_node;
	tmp2->prev = new_node;
}


t_token	*ft_find_head(t_token **last)
{
	t_token	*node;

	node = *last;
	while (node->prev)
		node = node->prev;
	return (node);
}
