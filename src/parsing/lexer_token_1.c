#include "../../include/minishell.h"

void	ft_pipe_token(int *i, t_pars *pars)
{
	printf(KYEL "-------------------- FT_PIPE_TOKEN --------------------\n" RESET);
	char	*tmp;

	tmp = NULL;
	tmp = ft_stock_char(tmp, pars->input[(*i)]);
	pars->type = PIPE;
	pars->nb_pipe += 1;
	(*i)++;
	ft_add_token_bottom(&pars->line, ft_create_node(tmp, pars));
	ft_freenull(tmp);
	ft_reset_node(pars);
}

void	ft_redin_token(int *i, t_pars *pars)
{
	printf(KYEL "-------------------- FT_REDIN_TOKEN --------------------\n" RESET);
	char	*tmp;

	tmp = NULL;
	tmp = ft_stock_char(tmp, pars->input[(*i)]);
	(*i)++;
	pars->type = REDIN;
	ft_add_token_bottom(&pars->line, ft_create_node(tmp, pars));
	ft_freenull(tmp);
	ft_reset_node(pars);
}

void	ft_redout_token(int *i, t_pars *pars)
{
	printf(KYEL "-------------------- FT_REDOUT_TOKEN --------------------\n" RESET);
	char	*tmp;

	tmp = NULL;
	tmp = ft_stock_char(tmp, pars->input[(*i)]);
	(*i)++;
	pars->type = REDOUT;
	ft_add_token_bottom(&pars->line, ft_create_node(tmp, pars));
	ft_freenull(tmp);
	ft_reset_node(pars);
}
