#include "../include/minishell.h"

void	ft_d_quotes_token(int *i, t_minishell *parse)
{
	char	*tmp;

	tmp = NULL;
	parse->type = D_QUOTES;
	parse->d_quotes = OPEN;
	printf(KYEL "-------------------- FT_D_QUOTES_TOKEN --------------------\n" RESET);
	while (parse->input[++(*i)] != '\"')
	{
		tmp = ft_stock_char(tmp, parse->input[*i]);
		if (parse->input[(*i)] == '$')
			parse->type = EXPAND;
	}
	if (parse->input[(*i)] == '\"')
	{
		parse->d_quotes = CLOSE;
		(*i)++;
	}
	printf("tmp = %s\n", tmp);
	if (parse->type == EXPAND)
		tmp = ft_quotes_expansion(tmp, parse);
	if (tmp)
		ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
	ft_freenull(tmp);
	parse->d_quotes = 0;
	parse->type = ARG;
	parse->flag_whitespace = 0;
}

void	ft_s_quotes_token(int *i, t_minishell *parse)
{
	char	*tmp;

	tmp = NULL;
	parse->type = S_QUOTES;
	parse->s_quotes = OPEN;
	printf(KYEL "-------------------- FT_S_QUOTES_TOKEN --------------------\n" RESET);
	while (parse->input[++(*i)] != '\'')
		tmp = ft_stock_char(tmp, parse->input[*i]);
	if (parse->input[(*i)] == '\'')
	{
		parse->s_quotes = CLOSE;
		(*i)++;
	}
	if (tmp)
		ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
	ft_freenull(tmp);
	parse->s_quotes = 0;
	parse->type = ARG;
	parse->flag_whitespace = 0;
}
