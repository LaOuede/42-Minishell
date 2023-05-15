#include "../include/minishell.h"

void	ft_d_quotes_token(int *i, t_minishell *parse)
{
	int		j;
	char	*tmp;

	j = *i;
	tmp = NULL;
	parse->d_quotes = OPEN;
	while (parse->input[j++])
	{
		if (parse->input[(j)] == 34)
		{
			parse->type = D_QUOTES;
			parse->d_quotes = CLOSED;
			break ;
		}
	}
	if (parse->type == D_QUOTES)
	{
		while (parse->input[(*i)++])
		{
			if (parse->input[(*i)] != 34)
				tmp = ft_stock_char(tmp, parse->input[*i]);
			if (parse->input[(*i)] == 34)
			{
				(*i)++;
				break ;
			}
		}
		ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
		parse->d_quotes = 0;
	}
	parse->type = ARG;
}

void	ft_s_quotes_token(int *i, t_minishell *parse)
{
	int		j;
	char	*tmp;

	j = *i;
	tmp = NULL;
	parse->s_quotes = OPEN;
	while (parse->input[j++])
	{
		if (parse->input[(j)] == 39)
		{
			parse->type = S_QUOTES;
			parse->s_quotes = CLOSED;
			break ;
		}
	}
	if (parse->type == S_QUOTES)
	{
		while (parse->input[(*i)++])
		{
			if (parse->input[(*i)] != 39)
				tmp = ft_stock_char(tmp, parse->input[*i]);
		}
		ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
		parse->s_quotes = 0;
	}
	parse->type = ARG;
}
