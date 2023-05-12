#include "../include/minishell.h"

t_minishell	*ft_init_parse(void)
{
	static t_minishell	*pars;

	if (!pars)
	{
		pars = ft_calloc(1, sizeof(t_minishell));
		pars->input = NULL;
		pars->line = NULL;
	}
	return (pars);
}

void	ft_parse(t_minishell *parse)
{
	if (!*parse->input)
		return ;
	ft_tokenization(parse);
	// TODO Penser à free la liste chaînée! :)
	// ft_free_lst(&parse->line);
}
