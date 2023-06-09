#include "../../include/minishell.h"

void	ft_s_quotes_token(int *i, t_pars *pars)
{
	printf(KYEL "-------------------- FT_S_QUOTES_TOKEN" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	char	*tmp;

	tmp = NULL;
	pars->type = ARG;
	pars->s_quotes = OPEN;
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
		ft_error_parsing(ERR_QUOTE, LEXER, pars);
	printf("s_quotes = %d\n", pars->s_quotes);
	if (tmp)
		ft_add_token_bottom(&pars->line, ft_create_node(tmp, pars));
	if (tmp)
		ft_reset_node(pars);
	ft_freenull(tmp);
	printf(KYEL "-------------------- FT_S_QUOTES_TOKEN" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
}

void	ft_char_quotes(int *i, char *str, t_pars *pars)
{
	printf(KYEL "-------------------- FT_CHAR_QUOTES --------------------\n" RESET);
	char	*tmp;

	tmp = NULL;
	while (str[(*i)] && str[(*i)] != '$')
	{
		printf("-> char = %c\n", str[(*i)]);
		tmp = ft_stock_char(tmp, str[(*i)]);
		(*i)++;
	}
	if (tmp)
	{
		ft_add_token_bottom(&pars->line, ft_create_node(tmp, pars));
		ft_freenull(tmp);
		ft_reset_node(pars);
	}
	printf("-> i = %d\n", (*i));
	printf("-> char fin = %c\n", pars->input[(*i)]);
}

char	*ft_stock_quotes(int *i, char *str, t_pars *pars)
{
	printf(KYEL "-------------------- FT_STOCK_QUOTES" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	while (pars->input[++(*i)])
	{
		if (pars->input[(*i)] == '\"')
			break ;
		str = ft_stock_char(str, pars->input[*i]);
		printf("-> char = %c\n", pars->input[(*i)]);
	}
	if (pars->input[(*i)] == '\"')
	{
		pars->d_quotes = CLOSE;
		(*i)++;
	}
	else
		ft_error_parsing(ERR_QUOTE, LEXER, pars);
	printf(KYEL "-------------------- FT_STOCK_QUOTES" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
	return (str);
}

void	ft_d_quotes_token(int *i, t_pars *pars)
{
	printf(KYEL "-------------------- FT_D_QUOTES_TOKEN" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	char	*str;
	int		j;
	size_t	len;

	str = NULL;
	pars->d_quotes = OPEN;
	printf("d_quotes = %d\n", pars->d_quotes);
	str = ft_stock_quotes(i, str, pars);
	len = ft_strlen(str);
	j = 0;
	while (j < (int)len)
	{
		printf("-> i = %d\n", j);
		printf("-> char = %c\n", str[j]);
		if (str[j] == '$')
			ft_envvar(&j, str, pars);
		else
			ft_char_quotes(&j, str, pars);
	}
	ft_freenull(str);
	printf(KYEL "-------------------- FT_D_QUOTES_TOKEN" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
}
