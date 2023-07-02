#include "../../include/minishell.h"

/*
Handle ' token
1) Look for closing s_quote.
2) If regular char, then stock char to memory and at the end create a new node.
3) Raise an error flag if quotes aren't closed.
*/
void	ft_s_quotes_token(int *i, t_ms *ms)
{
	char	*tmp;

	tmp = NULL;
	ms->pars->type = ARG;
	ms->pars->s_quotes = OPEN;
	while (ms->pars->input[++(*i)])
	{
		if (ms->pars->input[(*i)] == '\'')
			break ;
		tmp = ft_stock_char(ms, tmp, ms->pars->input[*i]);
	}
	if (ms->pars->input[(*i)] == '\'')
	{
		ms->pars->s_quotes = CLOSE;
		(*i)++;
	}
	else
		ft_error_parsing(ERR_QUOTE, LEXER, 2, ms);
	if (tmp)
	{
		ft_add_token_bottom(&ms->pars->line, ft_create_node(ms, tmp, ms->pars));
		ft_reset_node(ms->pars);
		tmp = ft_freenull(tmp);
	}
}

/*
1) Stock char to memory and at the end create a new node.
2) Return if $ char.
*/
void	ft_char_quotes(int *i, char *str, t_ms *ms)
{
	char	*tmp;

	tmp = NULL;
	while (str[(*i)] && str[(*i)] != '$')
	{
		tmp = ft_stock_char(ms, tmp, str[(*i)]);
		(*i)++;
	}
	if (tmp)
	{
		ft_add_token_bottom(&ms->pars->line, ft_create_node(ms, tmp, ms->pars));
		tmp = ft_freenull(tmp);
		ft_reset_node(ms->pars);
	}
}

/*
1) Look for closing d_quote.
2) Raise an error flag if quotes aren't closed.
*/
char	*ft_stock_quotes(int *i, char *str, t_ms *ms)
{
	while (ms->pars->input[++(*i)])
	{
		if (ms->pars->input[(*i)] == '\"')
			break ;
		str = ft_stock_char(ms, str, ms->pars->input[*i]);
	}
	if (ms->pars->input[(*i)] == '\"')
	{
		ms->pars->d_quotes = CLOSE;
		(*i)++;
	}
	else
		ft_error_parsing(ERR_QUOTE, LEXER, 2, ms);
	return (str);
}

/*
Handle " token
1) Look for closing d_quote.
2) Look for expansion in string.
*/
void	ft_d_quotes_token(int *i, t_ms *ms)
{
	int		j;
	size_t	len;
	char	*str;

	str = NULL;
	ms->pars->d_quotes = OPEN;
	str = ft_stock_quotes(i, str, ms);
	len = ft_strlen(str);
	j = 0;
	while (j < (int)len)
	{
		if (str[j] == '$')
			ft_envvar(&j, str, ms);
		else
			ft_char_quotes(&j, str, ms);
	}
	str = ft_freenull(str);
}

void	ft_token(int *i, t_ms *ms)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_stock_char(ms, tmp, ms->pars->input[(*i)]);
	if (ms->pars->input[(*i)] == '>')
		ms->pars->type = REDOUT;
	else if (ms->pars->input[(*i)] == '<')
		ms->pars->type = REDIN;
	else
	{
		ms->pars->type = PIPE;
		ms->pars->nb_pipe += 1;
	}
	ft_add_token_bottom(&ms->pars->line, ft_create_node(ms, tmp, ms->pars));
	(*i)++;
	tmp = ft_freenull(tmp);
	ft_reset_node(ms->pars);
}
