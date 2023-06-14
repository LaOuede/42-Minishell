#include "../../include/minishell.h"

void	ft_free_jct(t_jct *jct)
{
	if (jct)
	{
		if (jct->tab)
			ft_free_3tab(jct);
		if (jct->fds_in)
			free(jct->fds_in);
		if (jct->fds_out)
			free(jct->fds_out);
		free(jct);
	}
}

void	ft_free_pars(t_pars *pars)
{
	if (pars)
	{
		if (pars->input)
			ft_freenull(pars->input);
		if (pars->line)
			ft_free_lst(&pars->line);
		free(pars);
	}
}

void	ft_free_lst(t_token **lst)
{
	t_token	*ptr;
	t_token	*tmp;

	if (!lst || !*lst)
		return ;
	ptr = *lst;
	while (ptr)
	{
		tmp = ptr->next;
		ft_freenull(ptr->str);
		free(ptr);
		ptr = tmp;
	}
	*lst = NULL;
}

void	ft_free_token(t_token *token)
{
	if (token)
	{
		if (token->str)
		{
			free(token->str);
			token->str = NULL;
		}
		free(token);
	}
}
