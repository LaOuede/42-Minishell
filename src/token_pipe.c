#include "../include/minishell.h"

void	ft_pipe_token(int *i, t_minishell *parse)
{
	char	*tmp;

	printf(KYEL "-------------------- FT_PIPE_TOKEN --------------------\n" RESET);
	tmp = NULL;
	tmp = ft_stock_char(tmp, parse->input[(*i)]);
	parse->type = PIPE;
	parse->nb_pipe += 1;
	ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
	(*i)++;
	parse->type = ARG;
	parse->flag_whitespace = 0;
}
