#include "../include/minishell.h"

t_token	*ft_create_node(char *str)
{
	t_token	*new_node;

	new_node = ft_calloc(1, sizeof(t_token));
	new_node->type = -1;
	new_node->str = ft_strdup(str);
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

void	ft_tokenization(t_minishell *pars)
{
	char	*str;
	t_token	*tmp;

	str = pars->input;
	ft_add_token_bottom(&pars->line, ft_create_node(str));
	tmp = pars->line;
	while (tmp)
	{
		printf("tmp->str = %s\n", tmp->str);
		tmp = tmp->next;
	}
	free(tmp);
}
