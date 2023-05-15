#include "../include/minishell.h"

void	ft_quotes_token(int *i, t_minishell *parse)
{
	int		j;
	char	*tmp;

	j = *i;
	tmp = NULL;
	while (parse->input[j++])
	{
		if (parse->input[(j)] == 34)
		{
			parse->type = D_QUOTES;
			parse->d_quotes_out = 1;
			break ;
		}
	}
	if (parse->type == D_QUOTES)
	{
		while (parse->input[(*i)++])
		{
			if (parse->input[(*i)] != 34)
				tmp = ft_stock_char(tmp, parse->input[*i]);
		}
		ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
	}
}
