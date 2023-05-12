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
	int	i = 0;
	t_token	*tmp;

	if (!*parse->input)
		return ;
	ft_tokenization(parse);
	// Print linked-list
	tmp = parse->line;
	i = 0;
	while (tmp)
	{
		printf("node[%i] = %s\n", i++, tmp->str);
		tmp = tmp->next;
	}
	free(tmp);
	// Free linked-list between prompt
	ft_free_lst(&parse->line);
}
