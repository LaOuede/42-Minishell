#include "../include/minishell.h"

void	ft_pipes_token(int *i, t_minishell *parse)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_stock_char(tmp, parse->input[(*i)]);
	parse->type = PIPE;
	parse->nb_pipe += 1;
	ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
	(*i)++;
	parse->type = ARG;
}
