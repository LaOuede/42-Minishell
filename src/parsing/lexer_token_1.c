#include "../../include/minishell.h"

/*
Handle ' token
1) Look for closing s_quote.
2) If regular char, then stock char to memory and at the end create a new node.
3) Raise an error flag if quotes aren't closed.
*/
void	ft_s_quotes_token(int *i, t_ms *ms)
{
	printf(KYEL "-------------------- FT_S_QUOTES_TOKEN" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	char	*tmp;

	tmp = NULL;
	ms->pars->type = ARG;
	ms->pars->s_quotes = OPEN;
	while (ms->pars->input[++(*i)])
	{
		if (ms->pars->input[(*i)] == '\'')
			break ;
		tmp = ft_stock_char(tmp, ms->pars->input[*i]);
	}
	if (ms->pars->input[(*i)] == '\'')
	{
		ms->pars->s_quotes = CLOSE;
		(*i)++;
	}
	else
		ft_error_parsing(ERR_QUOTE, LEXER, 2, ms->pars);
	printf("s_quotes = %d\n", ms->pars->s_quotes);
	if (tmp)
	{	
		ft_add_token_bottom(&ms->pars->line, ft_create_node(tmp, ms->pars));
		ft_reset_node(ms->pars);
		ft_freenull(tmp);
	}
	printf(KYEL "-------------------- FT_S_QUOTES_TOKEN" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
}

/*
1) Stock char to memory and at the end create a new node.
2) Return if $ char.
*/
void	ft_char_quotes(int *i, char *str, t_ms *ms)
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
		ft_add_token_bottom(&ms->pars->line, ft_create_node(tmp, ms->pars));
		ft_freenull(tmp);
		ft_reset_node(ms->pars);
	}
	printf("-> i = %d\n", (*i));
	printf("-> char fin = %c\n", ms->pars->input[(*i)]);
}

/*
1) Look for closing d_quote.
2) Raise an error flag if quotes aren't closed.
*/
char	*ft_stock_quotes(int *i, char *str, t_ms *ms)
{
	printf(KYEL "-------------------- FT_STOCK_QUOTES" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	while (ms->pars->input[++(*i)])
	{
		if (ms->pars->input[(*i)] == '\"')
			break ;
		str = ft_stock_char(str, ms->pars->input[*i]);
		printf("-> char = %c\n", ms->pars->input[(*i)]);
	}
	if (ms->pars->input[(*i)] == '\"')
	{
		ms->pars->d_quotes = CLOSE;
		(*i)++;
	}
	else
		ft_error_parsing(ERR_QUOTE, LEXER, 2, ms->pars);
	printf(KYEL "-------------------- FT_STOCK_QUOTES" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
	return (str);
}

/*
Handle " token
1) Look for closing d_quote.
2) Look for expansion in string.
*/
void	ft_d_quotes_token(int *i, t_ms *ms)
{
	printf(KYEL "-------------------- FT_D_QUOTES_TOKEN" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	int		j;
	size_t	len;
	char	*str;

	str = NULL;
	ms->pars->d_quotes = OPEN;
	printf("d_quotes = %d\n", ms->pars->d_quotes);
	str = ft_stock_quotes(i, str, ms);
	len = ft_strlen(str);
	j = 0;
	while (j < (int)len)
	{
		printf("-> i = %d\n", j);
		printf("-> char = %c\n", str[j]);
		if (str[j] == '$')
			ft_envvar(&j, str, ms);
		else
			ft_char_quotes(&j, str, ms);
	}
	ft_freenull(str);
	printf(KYEL "-------------------- FT_D_QUOTES_TOKEN" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
}

void	ft_token(int *i, t_ms *ms)
{
	printf(KYEL "-------------------- FT_TOKEN --------------------\n" RESET);
	char	*tmp;

	tmp = NULL;
	tmp = ft_stock_char(tmp, ms->pars->input[(*i)]);
	if (ms->pars->input[(*i)] == '>')
		ms->pars->type = REDOUT;
	else if (ms->pars->input[(*i)] == '<')
		ms->pars->type = REDIN;
	else
	{
		ms->pars->type = PIPE;
		ms->pars->nb_pipe += 1;
	}
	ft_add_token_bottom(&ms->pars->line, ft_create_node(tmp, ms->pars));
	(*i)++;
	ft_freenull(tmp);
	ft_reset_node(ms->pars);
}
