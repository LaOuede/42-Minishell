#include "../include/minishell.h"

void	ft_redin_token(int *i, t_pars *pars)
{
	char	*tmp;

	printf(KYEL "-------------------- FT_REDIN_TOKEN --------------------\n" RESET);
	tmp = NULL;
	tmp = ft_stock_char(tmp, pars->input[(*i)]);
	pars->type = REDIN;
	ft_add_token_bottom(&pars->line, ft_create_node(tmp, pars));
	(*i)++;
	ft_reset_node(pars);
}

void	ft_redout_token(int *i, t_pars *pars)
{
	char	*tmp;

	printf(KYEL "-------------------- FT_REDOUT_TOKEN --------------------\n" RESET);
	tmp = NULL;
	tmp = ft_stock_char(tmp, pars->input[(*i)]);
	pars->type = REDOUT;
	ft_add_token_bottom(&pars->line, ft_create_node(tmp, pars));
	(*i)++;
	ft_reset_node(pars);
}

void	ft_appenred_token(int *i, t_pars *pars)
{
	char	*tmp;

	tmp = NULL;
	printf(KYEL "-------------------- FT_APPENRED_TOKEN --------------------\n" RESET);
	while (pars->input[(*i)] == '<')
	{
		tmp = ft_stock_char(tmp, pars->input[(*i)]);
		(*i)++;
	}
	pars->type = APPRED;
	ft_add_token_bottom(&pars->line, ft_create_node(tmp, pars));
	(*i)++;
	ft_reset_node(pars);
}

void	ft_heredoc_token(int *i, t_pars *pars)
{
	char	*tmp;

	tmp = NULL;
	printf(KYEL "-------------------- FT_HEREDOC_TOKEN --------------------\n" RESET);
	while (pars->input[(*i)] == '>')
	{
		tmp = ft_stock_char(tmp, pars->input[(*i)]);
		(*i)++;
	}
	pars->type = HEREDOC;
	ft_add_token_bottom(&pars->line, ft_create_node(tmp, pars));
	(*i)++;
	ft_reset_node(pars);
}
