#include "../include/minishell.h"

void	ft_free_lst(t_token **lst)
{
	t_token	*ptr;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		ptr = (*lst)->next;
		ft_freenull(*lst);
		*lst = ptr;
	}
	*lst = NULL;
}

void	ft_free_token(t_token *token)
{
	if (token)
	{
		if (token->str)
			ft_freenull(token->str);
		ft_freenull(token);
	}
}