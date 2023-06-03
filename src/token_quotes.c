#include "../include/minishell.h"

void	ft_s_quotes_token(int *i, t_pars *pars)
{
	printf(KYEL "-------------------- FT_S_QUOTES_TOKEN" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	char	*tmp;

	tmp = NULL;
	pars->type = S_QUOTES;
	pars->s_quotes = OPEN;
	printf("s_quotes = %d\n", pars->s_quotes);
	while (pars->input[++(*i)])
	{
		if (pars->input[(*i)] == '\'')
			break ;
		tmp = ft_stock_char(tmp, pars->input[*i]);
	}
	if (pars->input[(*i)] == '\'')
	{
		pars->s_quotes = CLOSE;
		(*i)++;
	}
	else
	{
		ft_error("Simple Quotes Error\n");
		printf("pars->flag_error_lexer = %d\n", pars->flag_error_lexer);
		pars->flag_error_lexer = false;
	}
	if (tmp)
		ft_add_token_bottom(&pars->line, ft_create_node(tmp, pars));
	if (tmp)
		ft_reset_node(pars);
	ft_freenull(tmp);
	printf(KYEL "-------------------- FT_S_QUOTES_TOKEN" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
}

char	*ft_stock_quotes(int *i, char *str, t_pars *pars)
{
	printf(KYEL "-------------------- FT_STOCK_QUOTES" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	while (pars->input[++(*i)])
	{
		if (pars->input[(*i)] == '\"')
			break ;
		if (pars->input[(*i)] == '$')
			pars->type = EXPAND;
		str = ft_stock_char(str, pars->input[*i]);
		printf("-> char = %c\n", pars->input[(*i)]);
	}
	if (pars->input[(*i)] == '\"')
	{
		pars->d_quotes = CLOSE;
		(*i)++;
	}
	else
	{
		ft_error("Double Quotes Error\n");
		printf("pars->flag_error_lexer = %d\n", pars->flag_error_lexer);
		pars->flag_error_lexer = false;
	}
	printf(KYEL "-------------------- FT_STOCK_QUOTES" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
	return (str);
}

void	ft_d_quotes_token(int *i, t_pars *pars)
{
	printf(KYEL "-------------------- FT_D_QUOTES_TOKEN" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	char	*tmp;

	tmp = NULL;
	pars->type = D_QUOTES;
	pars->d_quotes = OPEN;
	printf("d_quotes = %d\n", pars->d_quotes);
	tmp = ft_stock_quotes(i, tmp, pars);
	printf("tmp = %s\n", tmp);
	if (pars->type == EXPAND)
		tmp = ft_quotes_expansion(tmp, pars);
	printf("d_quotes = %d\n", pars->d_quotes);
	if (tmp)
		ft_add_token_bottom(&pars->line, ft_create_node(tmp, pars));
	if (tmp)
		ft_reset_node(pars);
	ft_freenull(tmp);
	printf(KYEL "-------------------- FT_D_QUOTES_TOKEN" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
}
