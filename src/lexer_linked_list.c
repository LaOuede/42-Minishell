#include "../include/minishell.h"

t_token	*ft_create_node(char *str, t_pars *pars)
{
	t_token	*new_node;

	new_node = ft_calloc(1, sizeof(t_token));
	new_node->type = pars->type;
	new_node->str = ft_strdup(str);
	new_node->nb_cmd = pars->nb_pipe;
	new_node->s_quotes = pars->s_quotes;
	new_node->d_quotes = pars->d_quotes;
	new_node->p_brackets = pars->p_brackets;
	new_node->c_brackets = pars->c_brackets;
	new_node->ws = pars->flag_whitespace;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	ft_insert_token(t_token **lst, t_token *prev, t_token *current, t_token *new_node)
{
	if (!new_node)
		return ;
	if (*lst == NULL)
	{
		return ;
	}
	new_node->type = CMD;
	new_node->prev = prev;
	prev->next = new_node;
	new_node->next = current;
	current->prev = new_node;
}

void	ft_add_token_top(t_token **lst, t_token *new_node)
{
	if (!new_node)
		return ;
	if (*lst == NULL)
	{
		*lst = new_node;
		new_node->prev = NULL;
		new_node->next = NULL;
		return ;
	}
	new_node->type = CMD;
	new_node->prev = NULL;
	new_node->next = *lst;
	*lst = new_node;
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

void	ft_remove_empty(t_token **list)
{
	printf(KYEL "-------------------- FT_REMOVE_EMPTY" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token *sup;
	t_token	*ptr;

	ptr = *list;
	while (ptr)
	{
		printf("TEST\n");
		if (!ptr->str)
		{
			sup = ptr;
			ft_free_token(sup);
		}
		ptr = ptr->next;
	}
	printf(KYEL "-------------------- FT_REMOVE_EMPTY" KRED " END " RESET KYEL "--------------------\n" RESET);
}
