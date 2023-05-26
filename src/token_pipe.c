#include "../include/minishell.h"

void	ft_pipe_token(int *i, t_pars *pars)
{
	char	*tmp;

	printf(KYEL "-------------------- FT_PIPE_TOKEN --------------------\n" RESET);
	tmp = NULL;
	tmp = ft_stock_char(tmp, pars->input[(*i)]);
	pars->type = PIPE;
	pars->nb_pipe += 1;
	ft_add_token_bottom(&pars->line, ft_create_node(tmp, pars));
	(*i)++;
	ft_reset_node(pars);
}
