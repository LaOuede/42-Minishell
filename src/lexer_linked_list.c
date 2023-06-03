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
	new_node->c_brackets = pars->c_brackets;
	new_node->ws = pars->flag_whitespace;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	ft_insert_token(t_token **lst, t_token *prev, t_token *current, t_token *new_node)
{
	printf(KYEL "-------------------- FT_INSERT_TOKEN" KGRN " START " RESET KYEL "--------------------\n" RESET);
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
	//printf("prev str = %s\n", prev->str);
	printf("new_node str = %s\n", new_node->str);
	printf("next str = %s\n", current->str);
	printf(KYEL "-------------------- FT_INSERT_TOKEN" KRED " END " RESET KYEL "--------------------\n" RESET);
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

void	ft_clean_list(t_token **list)
{
	printf(KYEL "-------------------- FT_CLEAN_LIST" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token *sup;
	t_token	*ptr;

	if (!*list)
		return ;
	ptr = *list;
	while (ptr->next)
	{
		printf("ptr->type = %d\n", ptr->type);
		if (ptr->next->type == ERROR)
		{
			sup = ptr->next;
			if (ptr->next->next)
			{
				ptr->next = ptr->next->next;
			}
			else if (!ptr->next->next)
			{
				ptr->next = NULL;
			}
			ft_free_token(sup);
		}
		else if (ptr->next)
			ptr = ptr->next;
	}
	printf(KYEL "-------------------- FT_CLEAN_LIST" KRED " END " RESET KYEL "--------------------\n" RESET);
}
